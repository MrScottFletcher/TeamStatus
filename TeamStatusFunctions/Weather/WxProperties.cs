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
        /// 0 = Clear, 1 = Few, 2 = Scattered, 3 = Broken, 4=Overcast
        /// Using 80x values from https://openweathermap.org/weather-conditions
        /// Or a corresponding value from rain/thunder/snow/ etc.
        /// </summary>
        public int Sky { get; set; } = 0;

        /// <summary>
        /// 0 = Calm, 2=Thunderstorm, 3=Drizzle, 5=Rain, 6=Snow, 7=Fog/Haze, 8=Squalls/Sand/Ash, 9=Tornado
        /// https://openweathermap.org/weather-conditions
        /// </summary>
        public int Wx { get; set; } = 0;

        /// <summary>
        /// 0 = none, 1 = advisory, 2 = Watch, 3=Warning
        /// Provided separately from weather.gov or other alert system
        /// </summary>
        public int WxAlert { get; set; } = 0;

        /// <summary>
        /// Simplified - if WeatherCondition meets a corresponding severe version of a value
        /// https://openweathermap.org/weather-conditions
        /// </summary>
        public bool WxSevere { get; set; }

        /// <summary>
        /// The amount of 'excitement' (or anxiety?) the weather might inspire.
        /// https://openweathermap.org/weather-conditions
        /// </summary>
        public int WxWow { get; set; }

        /// <summary>
        /// Simplified - if WeatherCondition = 2xx
        /// https://openweathermap.org/weather-conditions
        /// </summary>
        public bool wxThndr { get; set; }

        /// <summary>
        /// Simplified - if WeatherCondition is 781 from openweather OR a Tornado WARNING is present
        /// https://openweathermap.org/weather-conditions
        /// </summary>
        public bool WxTrndo { get; set; } = false;
    }
}
