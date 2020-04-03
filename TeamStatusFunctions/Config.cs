using System;
using System.Collections.Generic;
using System.Text;

namespace TeamStatusFunctions
{
    public class Config
    {
        public string VstsToken { get; set; }
        public string DeviceConnectionString { get; set; }
        public string DeviceName { get; set; }
        public string DeviceZipCode { get; set; }

        public string WxApiKey { get; set; }
        public string VstsHostName { get; set; }
        public string VstsArea { get; set; }
        public string VstsUser { get; set; }

        /// <summary>
        /// Required by the National Weather Service to identify this consumer of the API
        /// </summary>
        public string nwsAppName { get; internal set; }
        /// <summary>
        /// Required by the National Weather Service to identify this consumer of the API
        /// </summary>
        public string nwsContactEmail { get; internal set; }
    }
}
