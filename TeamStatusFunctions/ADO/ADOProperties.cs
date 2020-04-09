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
        public TeamInfo Team1 { get; set; }
        public TeamInfo Team2 { get; set; }
    }

    public class TeamInfo
    {
        public string ShortName { get; set; }
        public int PRCount { get; set; }
        public int Health { get; set; }
        public bool ProdAlert { get; set; }
        public bool ProdOutage { get; set; }
    }
}
