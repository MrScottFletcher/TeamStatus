using System;
using System.Collections.Generic;
using System.Text;

namespace TeamStatusFunctions
{
    public class ADOProperties
    {
        public ADODesired Desired { get; set; } = new ADODesired();
    }

    public class ADODesired
    {
        public int PRCount { get; set; } = 0;
    }
}
