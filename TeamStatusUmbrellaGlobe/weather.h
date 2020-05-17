
enum DisplayModeEnum {
    Weather_Clear,
    Weather_Rain,
    Weather_Snow,
    Weather_SevereWeather_ALERT,
    PullRequest_Pending,
};

enum DayPartEnum {
    Daypart_Night = 0,
    Daypart_Sunrise = 1,
    Daypart_Day = 2,
    Daypart_Sunset = 3,
};

class WeatherState {
  time_t startTime;
  DisplayModeEnum displayMode;
  DayPartEnum dayPart;
  int dayPartCode;
  double tempF = 0;
  bool bSevere;
  String wxAlert;
  String zipCode;
  int skyCode;
  int wxEnergy;
  int wxCode;
  bool bThunder;
  int (*ledFunction)();
};

static double tempF = 0;

static WeatherState currentWx;
static WeatherState updateWx;
