using Flurl.Http;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace TeamStatusFunctions
{
    public static class Weather
    {
        public static async Task<WxProperties> GetWeatherForZipCode(string zipCode, string wxApiKey, string nwsAppName, string nwsContactEmail)
        {
            WxProperties p = null;
            WxDesired d = null;

            var wxUrl = $"http://api.openweathermap.org/data/2.5/weather?units=imperial&zip={zipCode}&APPID={wxApiKey}";

            OpenWeatherResponse r = null;
            using (var fc = new FlurlClient())
            {
                var wxJson = await wxUrl.WithClient(fc).GetJsonAsync();
                r = GetOpenWeatherResponse(wxJson);
            }
            if (r != null)
            {
                d = GetWeatherPropertiesFromOpenWxResponse(r);
            }

            if (r != null && d != null)
            {
                #region weather.gov URL parameters:
                //status - Available values : actual, exercise, system, test, draft
                //message_type - Available values : alert, update, cancel
                //event - Event name
                //code - Event code
                //urgency - Available values : unknown, past, future, expected, immediate
                //severity - Available values : unknown, minor, moderate, severe, extreme
                //certainty - Available values : unknown, unlikely, possible, likely, observed
                #endregion

                //User-Agent information available here
                //https://www.weather.gov/documentation/services-web-api

                var alertUrl = $"https://api.weather.gov/alerts/active?status=actual&message_type=alert,update&point={r.Latitude}%2C{r.Longitude}&severity=severe,extreme";
                using (var fc = new FlurlClient())
                {
                    var alertJson = await alertUrl.WithClient(fc)
                        .WithHeaders(new
                        {
                            Accept = "application/geo+json",
                            User_Agent = $"({nwsAppName}, {nwsContactEmail})" // For NWS contact info - will eventually be an API key apparently
                        }).GetJsonAsync();

                    ApplyWxAlertResponse(alertJson, d);
                }
            }

            if (d != null)
            {
                p = new WxProperties
                {
                    Desired = d
                };
            }

            return p;
        }

        private static WxDesired GetWeatherPropertiesFromOpenWxResponse(OpenWeatherResponse r)
        {
            WxDesired d = new WxDesired();

            #region Assign generic weather attributes based on the OpenWeather response
            switch (r.ConditionId)
            {
                //Could have grouped these by 100's, but would have needed the switch for details anyway.
                //===============================================
                // Group 2xx: Thunderstorm
                //-----------------------------------------------
                case 200: // thunderstorm with light rain
                case 231: // thunderstorm with drizzle
                case 210: // light thunderstorm
                case 211: // thunderstorm
                case 221: // ragged thunderstorm
                case 230: // thunderstorm with light drizzle
                    d.Wx = 2;
                    d.Sky = 4; //Overcast
                    d.IsLightning = true;
                    d.WxIntensity = 3;
                    break;

                case 201: // thunderstorm with rain
                    d.Wx = 2;
                    d.Sky = 4; //Overcast
                    d.IsLightning = true;
                    d.WxIntensity = 5;
                    break;

                case 202: // thunderstorm with heavy rain
                case 212: // heavy thunderstorm
                case 232: // thunderstorm with heavy drizzle
                    d.Wx = 2;
                    d.Sky = 4; //Overcast
                    d.IsLightning = true;
                    d.WxIntensity = 7;
                    break;
                //===============================================
                // Group 3xx: Drizzle
                //-----------------------------------------------
                case 300: // light intensity drizzle
                case 310: // light intensity drizzle rain
                    d.Wx = 3;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 2;
                    break;
                case 301: // drizzle
                case 311: // drizzle rain
                case 313: // shower rain and drizzle
                case 321: // shower drizzle
                    d.Wx = 3;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 5;
                    break;
                case 302: // heavy intensity drizzle
                case 312: // heavy intensity drizzle rain
                case 314: // heavy shower rain and drizzle
                    d.Wx = 3;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 7;
                    break;
                //===============================================
                // Group 5xx: Rain
                //-----------------------------------------------
                case 500: // light rain
                case 520: // light intensity shower rain
                    d.Wx = 5;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 2;
                    break;
                case 501: // moderate rain
                case 511: // freezing rain
                    d.Wx = 5;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 5;
                    break;
                case 521: // shower rain
                case 531: // ragged shower rain
                    d.Wx = 5;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 7;
                    break;
                case 522: // heavy intensity shower rain
                case 502: // heavy intensity rain
                case 503: // very heavy rain
                case 504: // extreme rain
                    d.Wx = 5;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 9;
                    break;
                //===============================================
                // Group 6xx: Snow
                //-----------------------------------------------
                case 600: // light snow
                case 612: // Light shower sleet
                    d.Wx = 6;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 1;
                    break;
                case 601: // Snow
                case 613: // Shower sleet
                case 615: // Light rain and snow
                case 616: // Rain and snow
                case 620: // Light shower snow
                    d.Wx = 6;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 3;
                    break;
                case 611: // Sleet
                    d.Wx = 6;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 6;
                    break;
                case 602: // Heavy snow
                case 621: // Shower snow
                case 622: // Heavy shower snow
                    d.Wx = 6;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 7;
                    break;

                //===============================================
                // Group 7xx: Atmosphere
                //-----------------------------------------------
                case 701: // mist
                case 711: // Smoke
                case 721: // Haze
                case 731: // sand / dust whirls
                case 741: // fog
                case 751: // sand
                case 761: // dust
                case 762: // volcanic ash
                case 771: // squalls
                    d.Wx = 7;
                    d.Sky = 3; //Broken
                    d.WxIntensity = 7;
                    break;

                //#####################################################
                //##################### TORNADO #######################
                //#####################################################
                case 781:
                    d.Wx = 9;
                    d.IsTornadoWarning = true;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 10;
                    break;

                //===============================================
                // Group 800: Clear
                //-----------------------------------------------
                case 800: // clear sky
                    d.Wx = 0;
                    d.Sky = 0; //Clear
                    d.WxIntensity = 0;
                    break;

                //===============================================
                // Group 80x: Clouds
                //-----------------------------------------------
                case 801: // few clouds: 11 - 25 %
                    d.Wx = 0;
                    d.Sky = 1; //Few
                    d.WxIntensity = 0;
                    break;
                case 802: // scattered clouds: 25 - 50 %
                    d.Wx = 0;
                    d.Sky = 2; //Scattered
                    d.WxIntensity = 0;
                    break;
                case 803: // broken clouds: 51 - 84 %
                    d.Wx = 0;
                    d.Sky = 3; //Broken
                    d.WxIntensity = 0;
                    break;
                case 804: // overcast clouds: 85 - 100 %
                    d.Wx = 0;
                    d.Sky = 4; //Overcast
                    d.WxIntensity = 0;
                    break;
                default:
                    //what to do here?
                    break;
            }
            #endregion

            //===========================
            //Daypart
            //0 Night, 1 Sunrise, 2 Daytime, 3 Sunset

            //30 minutes before and after sunset
            long setWindow = 1800;

            //default to night.
            d.DayPart = 0;

            if (r.CurrentDateTimeUnixUTC > (r.SunriseUnixUTC - setWindow) && r.CurrentDateTimeUnixUTC <= (r.SunriseUnixUTC + setWindow))
                d.DayPart = 1; //SUNRISE -- within x minutes of sunrise either way
            if (r.CurrentDateTimeUnixUTC > (r.SunriseUnixUTC + setWindow) && r.CurrentDateTimeUnixUTC <= (r.SunsetUnixUTC - setWindow))
                d.DayPart = 2; //DAYTIME
            else if (r.CurrentDateTimeUnixUTC > (r.SunsetUnixUTC - setWindow) && r.CurrentDateTimeUnixUTC <= (r.SunsetUnixUTC + setWindow))
                d.DayPart = 3; //SUNSET -- within x minutes of sunset either way

            //===========================
            //TEMP - is Fahrenheit if you ask units=imperial during HTTP query
            d.TempF = r.Temperature;
            //===========================
            //Wind makes everything more intense, right?  +1 per 10mph
            int windFactor = Convert.ToInt32(r.WindSpeed / 10);
            d.WxIntensity += windFactor;

            if (d.WxIntensity > 10)
                d.WxIntensity = 10;
            //===========================
            return d;
        }

        private static OpenWeatherResponse GetOpenWeatherResponse(dynamic wxJson)
        {
            OpenWeatherResponse r = new OpenWeatherResponse();

            #region example json from Openweathermap.org
            //{
            //  "coord": { "lon": -122.08,"lat": 37.39},
            //  "weather": [
            //    {
            //      "id": 800,
            //      "main": "Clear",
            //      "description": "clear sky",
            //      "icon": "01d"
            //    }
            //  ],
            //  "base": "stations",
            //  "main": {
            //    "temp": 282.55,
            //    "feels_like": 281.86,
            //    "temp_min": 280.37,
            //    "temp_max": 284.26,
            //    "pressure": 1023,
            //    "humidity": 100
            //  },
            //  "visibility": 16093,
            //  "wind": {
            //    "speed": 1.5,
            //    "deg": 350
            //  },
            //  "clouds": {
            //    "all": 1
            //  },
            //  "dt": 1560350645,
            //  "sys": {
            //    "type": 1,
            //    "id": 5122,
            //    "message": 0.0139,
            //    "country": "US",
            //    "sunrise": 1560343627,
            //    "sunset": 1560396563
            //  },
            //  "timezone": -25200,
            //  "id": 420006353,
            //  "name": "Mountain View",
            //  "cod": 200
            //}
            #endregion

            try { r.Temperature = wxJson.main.temp; }
            catch (Exception exAssign) { throw new InvalidCastException("Error assigning Temperature. " + exAssign.ToString()); }
            try { r.ConditionId = wxJson.weather[0].id; }
            catch (Exception exAssign) { throw new InvalidCastException("Error assigning ConditionId. " + exAssign.ToString()); }
            try { r.ConditionMain = wxJson.weather[0].main; }
            catch (Exception exAssign) { throw new InvalidCastException("Error assigning ConditionMain. " + exAssign.ToString()); }
            try { r.WindSpeed = wxJson.wind.speed; }
            catch (Exception exAssign) { throw new InvalidCastException("Error assigning WindSpeed. " + exAssign.ToString()); }
            try { r.WindDirection = wxJson.wind.deg; }
            catch (Exception exAssign) { throw new InvalidCastException("Error assigning WindDirection. " + exAssign.ToString()); }
            try { r.Latitude = wxJson.coord.lat; }
            catch (Exception exAssign) { throw new InvalidCastException("Error assigning Latitude. " + exAssign.ToString()); }
            try { r.Longitude = wxJson.coord.lon; }
            catch (Exception exAssign) { throw new InvalidCastException("Error assigning Longitude. " + exAssign.ToString()); }
            try { r.SunriseUnixUTC = wxJson.sys.sunrise; }
            catch (Exception exAssign) { throw new InvalidCastException("Error assigning SunriseUnixUTC. " + exAssign.ToString()); }
            try { r.SunsetUnixUTC = wxJson.sys.sunset; }
            catch (Exception exAssign) { throw new InvalidCastException("Error assigning SunsetUnixUTC. " + exAssign.ToString()); }
            try { r.CurrentDateTimeUnixUTC = wxJson.dt; }
            catch (Exception exAssign) { throw new InvalidCastException("Error assigning CurrentDateTimeUnixUTC. " + exAssign.ToString()); }
            return r;
        }

        private static WxDesired ApplyWxAlertResponse(dynamic wxJson, WxDesired d)
        {
            bool isTornadoWarning = false;
            bool isSevere = false; // severity = "Severe"
            int alertLevel = 0; //0 = none, 1 = advisory, 2 = Watch, 3 = Warning

            foreach (var f in wxJson.features)
            {
                //Use "@" to prefix property names that are otherwise reserved words. :) 
                string eventName = f.properties.@event.ToLower();

                if (!eventName.Contains("flood"))
                {
                    if (eventName.Contains("advisory"))
                        if (alertLevel < 1)
                            alertLevel = 1;
                    if (eventName.Contains("watch"))
                        if (alertLevel < 2)
                            alertLevel = 2;
                    if (eventName.Contains("warning"))
                        if (alertLevel < 3)
                        {
                            alertLevel = 3;
                            if (eventName.Contains("tornado"))
                            {
                                isTornadoWarning = true;
                            }
                        }

                    string severity = f.properties.severity.ToLower();
                    if (severity == "severe")
                        isSevere = true;
                }
            }

            d.WxAlertLevel = alertLevel;
            d.IsTornadoWarning = isTornadoWarning;
            d.WxAlertSevere = isSevere;

            return d;
        }

        public class OpenWeatherResponse
        {
            public long ConditionId { get; set; }
            public string ConditionMain { get; set; }
            public double Temperature { get; set; }
            public double WindSpeed { get; set; }
            public double WindDirection { get; set; }
            public double Latitude { get; set; }
            public double Longitude { get; set; }

            /// <summary>
            /// Time of data calculation, unix, UTC
            /// </summary>
            public long CurrentDateTimeUnixUTC { get; set; }

            /// <summary>
            /// Sunrise time, unix, UTC
            /// </summary>
            public long SunriseUnixUTC { get; set; }

            /// <summary>
            /// Sunset time, unix, UTC
            /// </summary>
            public long SunsetUnixUTC { get; set; }

            /// <summary>
            ///  Shift in seconds from UTC
            /// </summary>
            public long TimezoneShiftSeconds { get; set; }
        }

        public static DateTime GetLocalDateTime(long unixEpoch, long timezoneOffsetSeconds)
        {
            return GetUTCDateTime(unixEpoch).AddSeconds(timezoneOffsetSeconds);
        }

        public static DateTime GetUTCDateTime(long unixEpoch)
        {
            var localDateTimeOffset = DateTimeOffset.FromUnixTimeSeconds(unixEpoch);
            return localDateTimeOffset.UtcDateTime;
        }
    }
}
