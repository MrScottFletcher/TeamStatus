using System;
using System.Collections.Generic;
using System.Text;

namespace TeamStatusFunctions
{
    public static class Utility
    {
        public static string GetEnvironmentVariable(string name)
        {
            return System.Environment.GetEnvironmentVariable(name, EnvironmentVariableTarget.Process);
        }
    }
}
