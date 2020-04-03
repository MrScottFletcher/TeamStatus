using System;
using System.Collections.Generic;
using System.Text;

namespace TeamStatusFunctions
{
    public class WxProperties
    {
        public WxDesired Desired { get; set; } = new WxDesired();
    }

    public class WxDesired
    {

        /// <summary>
        /// Temperature in Fahrenheit 
        /// </summary>
        public double TempF { get; set; } = 0;

        /// <summary>
        /// 0 Night, 1 Sunrise, 2 Daytime, 3 Sunset
        /// </summary>
        public int DayPart { get; set; } = 0;

        /// <summary>
        /// 0 = none, 1 = advisory, 2 = Watch, 3=Warning
        /// Provided separately from weather.gov or other alert system
        /// </summary>
        public int WxAlertLevel { get; set; } = 0;

        /// <summary>
        /// Simplified - if WeatherCondition meets a corresponding severe version of a value
        /// https://openweathermap.org/weather-conditions
        /// </summary>
        public bool WxAlertSevere { get; set; }

        /// <summary>
        /// 0 = Clear, 1 = Few, 2 = Scattered, 3 = Broken, 4=Overcast
        /// Using 80x values from https://openweathermap.org/weather-conditions
        /// Or a corresponding value from rain/thunder/snow/ etc.
        /// </summary>
        public int Sky { get; set; } = 0;

        /// <summary>
        /// 0 = Clear, 2=Thunderstorm, 3=Drizzle, 5=Rain, 6=Snow, 7=Fog/Haze, 8=Clouds, 9=Tornado
        /// https://openweathermap.org/weather-conditions
        /// </summary>
        public int Wx { get; set; } = 0;

        /// <summary>
        /// Simplified - if WeatherCondition = 2xx
        /// https://openweathermap.org/weather-conditions
        /// </summary>
        public bool IsLightning { get; set; }

        /// <summary>
        /// Simplified - if WeatherCondition meets a corresponding severe version of a value
        /// https://openweathermap.org/weather-conditions
        /// </summary>
        public int WxIntensity { get; set; }

        /// <summary>
        /// Simplified - if WeatherCondition is 781 from openweather OR a Tornado WARNING is present
        /// https://openweathermap.org/weather-conditions
        /// </summary>
        public bool IsTornadoWarning { get; set; } = false;
    }
}
