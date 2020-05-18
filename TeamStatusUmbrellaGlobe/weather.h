
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

//      "ZipCode": "61614",
//      "tempF": 66.72,
//      "dayPart": 2,
//      "sky": 4,
//      "wx": 5,
//      "wxAlert": 0,
//      "wxSevere": false,
//      "wxWow": 6,
//      "wxThndr": false,
//      "wxTrndo": false,
    
    typedef void (*voidFuncPtr)(void);// Create a type to point to a funciton.
  public:
    long startTicks();
    time_t startTime();
    DisplayModeEnum displayMode();
    DayPartEnum dayPart();
    int dayPartCode();
    double tempF();
    bool bSevere();
    String wxAlert();
    String zipCode();
    int skyCode();
    int wxEnergy();
    int wxCode();
    bool bThunder();
    bool bTornado();

    void zipCode_set(String p);
    void startTicks_set(long p);
    void startTime_set(time_t p);
    void dayPartCode_set(int p);
    void tempF_set(double p);
    void bSevere_set(bool p);
    void wxAlert_set(String p);
    void skyCode_set(int p);
    void wxEnergy_set(int p);
    void wxCode_set(int p);
    void bThunder_set(bool p);
    void bTornado_set(bool p);

    bool IsDifferent(WeatherState other);

    //int (*ledFunction)();
    int getLEDFunction();
    void setLEDFunction(voidFuncPtr);
  private:
    long _startTicks;
    time_t _startTime;
    DisplayModeEnum _displayMode;
    DayPartEnum _dayPart;
    int _dayPartCode;
    double _tempF = 0;
    bool _bSevere;
    String _wxAlert;
    String _zipCode;
    int _skyCode;
    int _wxEnergy;
    int _wxCode;
    bool _bThunder;
    bool _bTornado;
    //int (*_ledFunction)();
    static voidFuncPtr _LEDFuncitonPointer; // Create an instance of the empty function pointer
};


//WeatherState::WeatherState(long startTicks){
//  //could set the current ticks here.  Just adding this to learn. :)
//  _startTicks = startTicks;
//}

//void(*) WeatherState::getLEDFunction(){
//  return *_LEDFuncitonPointer;
//}

//void WeatherState::setLEDFunction(*_ledFunction){
//  _LEDFuncitonPointer = _ledFunction;
//}

bool WeatherState::IsDifferent(WeatherState other){
  if(this->_dayPartCode != other.dayPartCode()){ Serial.println("dayPartCode changed..."); return true;}
  else if(this->_tempF != other.tempF()){ Serial.println("tempF changed..."); return true;}
  else if(this->_bSevere != other.bSevere()){ Serial.println("bSevere changed..."); return true;}
  else if(this->_wxAlert != other.wxAlert()){ Serial.println("wxAlert changed..."); return true;}
  else if(this->_zipCode != other.zipCode()){ Serial.println("zipCode changed..."); return true;}
  else if(this->_skyCode != other.skyCode()){ Serial.println("skyCode changed..."); return true;}
  else if(this->_wxEnergy != other.wxEnergy()){ Serial.println("wxEnergy changed..."); return true;}
  else if(this->_wxCode != other.wxCode()){ Serial.println("wxCode changed..."); return true;}
  else if(this->_bThunder != other.bThunder()){ Serial.println("bThunder changed..."); return true;}
  else if(this->_bTornado != other.bTornado()){ Serial.println("bTornado changed..."); return true;}
  else return false;
}

long WeatherState::startTicks(){
  return _startTicks;
}
void WeatherState::startTicks_set(long p){
  this->_startTicks = p;
}
//--------------------
time_t WeatherState::startTime(){
  return _startTime;
}
void WeatherState::startTime_set(time_t p){
  this->_startTime = p;
}
//--------------------
DisplayModeEnum WeatherState::displayMode(){
  return _displayMode;
}
//--------------------
DayPartEnum WeatherState::dayPart(){
  return _dayPart;
}
//--------------------
int WeatherState::dayPartCode(){
  return _dayPartCode;
}
void WeatherState::dayPartCode_set(int p){
  this->_dayPartCode = p;
}
//--------------------
double WeatherState::tempF(){
  return _tempF;
}
void WeatherState::tempF_set(double p){
  this->_tempF = p;
}
//--------------------
bool WeatherState::bSevere(){
  return _bSevere;
}
void WeatherState::bSevere_set(bool p){
  this->_bSevere = p;
}
//--------------------
String WeatherState::wxAlert(){
  return _wxAlert;
}
void WeatherState::wxAlert_set(String p){
  this->_wxAlert = p;
}
//--------------------
String WeatherState::zipCode(){
  return _zipCode;
}
void WeatherState::zipCode_set(String p){
  this->_zipCode = p;
}
//--------------------
int WeatherState::skyCode(){
  return _skyCode;
}
void WeatherState::skyCode_set(int p){
  this->_skyCode = p;
}
//--------------------
int WeatherState::wxEnergy(){
  return _wxEnergy;
}
void WeatherState::wxEnergy_set(int p){
  this->_wxEnergy = p;
}
//--------------------
int WeatherState::wxCode(){
  return _wxCode;
}
void WeatherState::wxCode_set(int p){
  this->_wxCode = p;
}
//--------------------
bool WeatherState::bThunder(){
  return _bThunder;
}
void WeatherState::bThunder_set(bool p){
  this->_bThunder = p;
}
//--------------------
bool WeatherState::bTornado(){
  return _bTornado;
}
void WeatherState::bTornado_set(bool p){
  this->_bTornado = p;
}
//--------------------

static double tempF = 0;
