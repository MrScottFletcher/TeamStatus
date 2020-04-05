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
using System.Collections.Generic;

namespace TeamStatusFunctions
{
    public static class WxTimerFunction
    {
        [FunctionName("WxTimerFunction")]
        public static void Run([TimerTrigger("0 */5 * * * *")]TimerInfo myTimer, ILogger log)
        {
            string stage = "";
            long deviceCount = 0;
            try
            {
                log.LogInformation($"C# Timer trigger function executed at {DateTime.Now}");

                var serializerSettings = new JsonSerializerSettings();
                serializerSettings.ContractResolver = new CamelCasePropertyNamesContractResolver();

                #region get CONFIG keys
                stage = $"Getting App key CONFIG_WX_APIKEY";
                string wxApiKey = Utility.GetEnvironmentVariable("CONFIG_WX_APIKEY");

                stage = $"Getting App key CONFIG_NWS_APPNAME";
                string nwsAppName = Utility.GetEnvironmentVariable("CONFIG_NWS_APPNAME");
                
                stage = $"Getting App key CONFIG_NWS_CONTACT_EMAIL";
                string nwsContactEmail = Utility.GetEnvironmentVariable("CONFIG_NWS_CONTACT_EMAIL");

                stage = $"Getting App key CONFIG_DEVICE_RW_CONNECTION_STRING";
                string connString = Utility.GetEnvironmentVariable("CONFIG_DEVICE_RW_CONNECTION_STRING");

                stage = $"CreateFromConnectionString...";
                RegistryManager rm = RegistryManager.CreateFromConnectionString(connString);
                #endregion

                stage = $"GetRegistryStatisticsAsync...";
                RegistryStatistics stats = rm.GetRegistryStatisticsAsync().Result;

                stage = $"checking stats.TotalDeviceCount...";
                deviceCount = stats.TotalDeviceCount;


                stage = $"TotalDeviceCount = {deviceCount.ToString()}";
                if (deviceCount > 0)
                {
                    string queryByZip = "select * from devices ORDER BY properties.reported.ZipCode";

                    stage = $"CreateQuery by Zip...'{queryByZip}'";
                    IQuery deviceQuery = rm.CreateQuery(queryByZip);

                    string currentZipCode = String.Empty;
                    string weatherPatch = null;

                    stage = $"while deviceQuery.HasMoreResults... ";

                    while (deviceQuery.HasMoreResults)
                    {
                        #region Get the next page of devices
                        stage = $"GetNextAsTwinAsync... ";
                        IEnumerable<Twin> page = null;
                        try
                        {
                            page = deviceQuery.GetNextAsTwinAsync().Result;
                        }
                        catch (Exception exQry)
                        {
                            //HEADS-UP!  Since properties.reported.ZipCode is dynamic, well get a Bad Request error if there 
                            //were no devices in the list.
                            log.LogInformation($"ERROR deviceQuery.GetNextAsTwinAsync with query '{queryByZip}'.  {DateTime.Now} - {exQry.ToString()}");
                            throw;
                        }
                        #endregion
                        
                        stage = $"foreach (var twin in page)... ";
                        foreach (var twin in page)
                        {
                            //get the zip code of the current twin
                            string twinZipCode = String.Empty;

                            stage = $"if (twin.Properties.Reported.Contains(ZipCode)... ";
                            if (twin.Properties.Reported.Contains("ZipCode"))
                                twinZipCode = twin.Properties.Reported["ZipCode"];

                            if (!String.IsNullOrEmpty(twinZipCode))
                            {
                                if (twinZipCode != currentZipCode)
                                {
                                    #region Get the Weather for new Zip Code
                                    //reset to detect a failure next
                                    weatherPatch = null;

                                    //If not the same zip code, get new weather
                                    currentZipCode = twinZipCode;
                                    stage = $"Weather.GetWeatherForZipCode... ";
                                    WxProperties wxProperties = Weather.GetWeatherForZipCode(currentZipCode, wxApiKey, nwsAppName, nwsContactEmail).Result;

                                    if (wxProperties != null)
                                    {
                                        stage = $"SerializeObject for weatherPatch... ";
                                        weatherPatch = JsonConvert.SerializeObject(new { Properties = wxProperties }, serializerSettings);
                                    }
                                    #endregion
                                }

                                if (weatherPatch != null)
                                {
                                    // do work on twin object
                                    stage = $"UpdateTwinAsync for twin deviceId: {twin.DeviceId} ";
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
                }
                else
                {
                    log.LogInformation($"No devices in the list.  Nothing to do. {DateTime.Now}");
                }

                //FYI - There is no response for timers

            }
            catch (Exception exAny)
            {
                log.LogInformation($"Error at stage '{stage}' with {deviceCount} devices: {DateTime.Now} : {exAny.ToString()} ");
                throw;
            }

        }
    }
}

