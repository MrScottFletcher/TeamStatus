using Microsoft.VisualStudio.TestTools.UnitTesting;
using TeamStatusFunctions;

namespace TeamStatusTest
{
    [TestClass]
    public class WxTests
    {
        const string OPENWEATHER_API_KEY = "YOUR-API-KEY-HERE";
        const string NWS_APP_NAME = "YOUR APP NAME HERE";
        const string NWS_CONTACT_EMAIL = "YOUR-EMAIL-ADDRESS-HERE";

        [TestMethod]
        public void GetWeatherForZipCodeTest_PeoriaIL()
        {
            var wx = Weather.GetWeatherForZipCode("61614", OPENWEATHER_API_KEY,NWS_APP_NAME, NWS_CONTACT_EMAIL).Result;

            Assert.IsNotNull(wx, "Expected result to be non-null");
        }
        
        [TestMethod]
        public void GetWeatherForZipCodeTest_SiouxFallsSD()
        {
            var wx = Weather.GetWeatherForZipCode("57101", OPENWEATHER_API_KEY,NWS_APP_NAME, NWS_CONTACT_EMAIL).Result;

            Assert.IsNotNull(wx, "Expected result to be non-null");
        }

        [TestMethod]
        public void GetWeatherForZipCodeTest_PalestineAR()
        {
            var wx = Weather.GetWeatherForZipCode("72372", OPENWEATHER_API_KEY,NWS_APP_NAME, NWS_CONTACT_EMAIL).Result;

            Assert.IsNotNull(wx, "Expected result to be non-null");
        }

        [TestMethod]
        public void GetWeatherForZipCodeTest_MarbleHillMO()
        {
            var wx = Weather.GetWeatherForZipCode("63764", OPENWEATHER_API_KEY,NWS_APP_NAME, NWS_CONTACT_EMAIL).Result;

            Assert.IsNotNull(wx, "Expected result to be non-null");
        }

        [TestMethod]
        public void GetWeatherForZipCodeTest_StPaulMN()
        {
            var wx = Weather.GetWeatherForZipCode("55130", OPENWEATHER_API_KEY,NWS_APP_NAME, NWS_CONTACT_EMAIL).Result;

            Assert.IsNotNull(wx, "Expected result to be non-null");
        }

    }
}
