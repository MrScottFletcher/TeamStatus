using System;
using System.Net;
using Newtonsoft.Json;
using System.Net.Http;
using System.Threading.Tasks;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Extensions.Logging;
using Flurl;
using Flurl.Http;
using Microsoft.Azure.Devices;
using Newtonsoft.Json.Serialization;
using Microsoft.Azure.Devices.Shared;

namespace TeamStatusFunctions
{
    public static class WxTimerFunction
    {
        [FunctionName("WxTimerFunction")]
        public static void Run([TimerTrigger("0 */5 * * * *")]TimerInfo myTimer, ILogger log)
        {
            log.LogInformation($"C# Timer trigger function executed at: {DateTime.Now}");

            var _config = new Formo.Configuration().Bind<Config>();

            var serializerSettings = new JsonSerializerSettings();
            serializerSettings.ContractResolver = new CamelCasePropertyNamesContractResolver();
            RegistryManager rm = RegistryManager.CreateFromConnectionString(_config.DeviceConnectionString);

            IQuery deviceQuery = rm.CreateQuery("select * from devices ORDER BY properties.reported.ZipCode");

            string currentZipCode = String.Empty;
            WxProperties wxProperties = null;
            string weatherPatch = null;
            while (deviceQuery.HasMoreResults)
            {
                var page = deviceQuery.GetNextAsTwinAsync().Result;
                foreach (var twin in page)
                {
                    //get the zip code of the current twin
                    string twinZipCode = String.Empty;
                    if(twin.Properties.Reported.Contains("ZipCode"))
                        twinZipCode = twin.Properties.Reported["ZipCode"];

                    if (!String.IsNullOrEmpty(twinZipCode))
                    {
                        if (twinZipCode != currentZipCode)
                        {
                            //If not the same zip code, get new weather
                            currentZipCode = twinZipCode;
                            wxProperties = Weather.GetWeatherForZipCode(currentZipCode, _config.WxApiKey, _config.nwsAppName, _config.nwsContactEmail).Result;
                            weatherPatch = JsonConvert.SerializeObject(new { Properties = wxProperties }, serializerSettings);
                        }

                        if (weatherPatch != null)
                        {
                            // do work on twin object
                            Twin updatedTwin = rm.UpdateTwinAsync(twin.DeviceId, weatherPatch, twin.ETag).Result;
                        }
                    }
                    else
                    {
                        //No ZipCode - not going to update the weather on this twin.  
                        //Log it? Do we care enough?
                    }
                }
            }


            //FYI - There is no response for timers
        }


    }
}

