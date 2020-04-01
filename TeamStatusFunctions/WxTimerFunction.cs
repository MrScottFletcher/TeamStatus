using System;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Extensions.Logging;

namespace TeamStatusFunctions
{
    public static class WxTimerFunction
    {
        [FunctionName("WxTimerFunction")]
        public static void Run([TimerTrigger("0 */5 * * * *")]TimerInfo myTimer, ILogger log)
        {
            log.LogInformation($"C# Timer trigger function executed at: {DateTime.Now}");

            var _config = new Formo.Configuration().Bind<Config>();

            var activePullRequests = await GetActivePullRequestsForArea(_config.VstsArea, _config.VstsUser, _config.VstsToken);
            var serializerSettings = new JsonSerializerSettings();
            serializerSettings.ContractResolver = new CamelCasePropertyNamesContractResolver();

            RegistryManager rm = RegistryManager.CreateFromConnectionString(_config.DeviceConnectionString);
            var twin = await rm.GetTwinAsync(_config.DeviceName);
            Properties properties = new Properties();
            switch (activePullRequests)
            {
                case 0:
                    properties.YouHaventDoneADamnThing();
                    break;
                case 1:
                    properties.MehWhenYouGetAChance();
                    break;
                case 2:
                    properties.MergeFight();
                    break;
                case 3:
                    properties.YoudBeProductiveIfSomeoneCared();
                    break;
                case 4:
                    properties.SeriouslyPeopleLookAtMe();
                    break;
                default:
                    properties.SeriouslyPeopleLookAtMe();
                    break;
            }

            var patch = JsonConvert.SerializeObject(new { Properties = properties }, serializerSettings);

            await rm.UpdateTwinAsync(twin.DeviceId, patch, twin.ETag);

            return req.CreateResponse(HttpStatusCode.OK, new { });
        }

        private static async Task<int> GetActivePullRequestsForArea(string areaName, string userName, string token)
        {
            int activeCount;
            var repoUrl = $"https://rlicorp.visualstudio.com/{areaName}/_apis/git/repositories?api-version=1.0";
            using (
                var fc = new FlurlClient().WithBasicAuth(userName, token))
            {
                var repositories = await repoUrl.WithClient(fc).GetJsonAsync();

                activeCount = 0;
                foreach (var repo in repositories.value)
                {
                    string url = repo.url.ToString();
                    var count = await url.AppendPathSegment("pullrequests")
                        .SetQueryParam("api-version", "1.0")
                        .SetQueryParam("status", "active")
                        .WithClient(fc)
                        .GetJsonAsync();
                    activeCount += count.count;
                }
            }
            return activeCount;
        }




    }
}
}
