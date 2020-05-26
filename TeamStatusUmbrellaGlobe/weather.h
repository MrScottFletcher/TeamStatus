
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
    
    //typedef void (*voidFuncPtr)(void);// Create a type to point to a funciton.
  public:
    long startTicks();
    time_t startTime();
    DisplayModeEnum displayMode();
    DayPartEnum dayPart();
    
    String zipCode();
    
    void zipCode_set(String p);
    bool zipCode_changed();
    
    void startTicks_set(long p);
    void startTime_set(long p);
   
    int dayPartCode();
    void dayPartCode_set(int p);
    bool dayPartCode_changed();
    void dayPartCode_changed_set(bool changed);
    
    double tempF();
    void tempF_set(double p);
    bool tempF_changed();
    void tempF_changed_set(bool changed);
    
    bool bSevere();
    void bSevere_set(bool p);
    bool bSevere_changed();
    void bSevere_changed_set(bool changed);

    int wxAlertLevel();
    void wxAlertLevel_set(int p);
    bool wxAlertLevel_changed();
    void wxAlertLevel_changed_set(bool changed);
    
    int skyCode();
    void skyCode_set(int p);
    bool skyCode_changed();
    void skyCode_changed_set(bool changed);

    int wxEnergy();
    void wxEnergy_set(int p);
    bool wxEnergy_changed();
    void wxEnergy_changed_set(bool changed);
    
    int wxCode();
    void wxCode_set(int p);
    bool wxCode_changed();
    void wxCode_changed_set(bool changed);
    
    bool bThunder();
    void bThunder_set(bool p);
    bool bThunder_changed();
    void bThunder_changed_set(bool changed);
    
    bool bTornado();
    void bTornado_set(bool p);
    bool bTornado_changed();
    void bTornado_changed_set(bool changed);

    int ledEffectIndex();
    void ledEffectIndex_set(int p);

    int ledBrightness();
    void ledBrightness_set(int p);

    int ledDelayMs();
    void ledDelayMs_set(int p);

    int sfxIndex();
    void sfxIndex_set(int p);

    bool IsDifferent(WeatherState other);

    //int (*ledFunction)();
//    int getLEDFunction();
//    void setLEDFunction(voidFuncPtr);
  private:
    long _startTicks;
    time_t _startTime;
    
//    DisplayModeEnum _displayMode;
//    DayPartEnum _dayPart;
    
    int _dayPartCode;
    bool _dayPartCode_changed;

    double _tempF = 0;
    bool _tempF_changed;

    bool _bSevere;
    bool _bSevere_changed;
    
    int _wxAlertLevel;
    bool _wxAlertLevel_changed;

    String _zipCode;

    int _skyCode;
    bool _skyCode_changed;

    int _wxEnergy;
    bool _wxEnergy_changed;

    int _wxCode;
    bool _wxCode_changed;

    bool _bThunder;
    bool _bThunder_changed;
    
    bool _bTornado;
    bool _bTornado_changed;

    int _ledEffectIndex;
    int _ledBrightness;
    int _ledDelayMs;
    int _sfxIndex;
    //int (*_ledFunction)();
    //static voidFuncPtr _LEDFuncitonPointer; // Create an instance of the empty function pointer
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
  if(this->_dayPartCode != other.dayPartCode()){ Serial.println("dayPartCode changed..."); this->_dayPartCode_changed = true; return true;}
  else if(this->_tempF != other.tempF()){ Serial.println("tempF changed..."); this->_tempF_changed = true; return true;}
  else if(this->_bSevere != other.bSevere()){ Serial.println("bSevere changed..."); this->_bSevere_changed = true; return true;} 
  else if(this->_wxAlertLevel != other.wxAlertLevel()){ Serial.println("wxAlertLevel changed..."); this->_wxAlertLevel_changed = true; return true;}
  else if(this->_skyCode != other.skyCode()){ Serial.println("skyCode changed..."); this->_skyCode_changed = true; return true;}
  else if(this->_wxEnergy != other.wxEnergy()){ Serial.println("wxEnergy changed..."); this->_wxEnergy_changed = true; return true;}
  else if(this->_wxCode != other.wxCode()){ Serial.println("wxCode changed..."); this->_wxCode_changed = true; return true;}
  else if(this->_bThunder != other.bThunder()){ Serial.println("bThunder changed..."); this->_bThunder_changed = true; return true;}
  else if(this->_bTornado != other.bTornado()){ Serial.println("bTornado changed..."); this->_bTornado_changed = true; return true;}
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
//DisplayModeEnum WeatherState::displayMode(){
//  return _displayMode;
//}
////--------------------
//DayPartEnum WeatherState::dayPart(){
//  return _dayPart;
//}
//--------------------
int WeatherState::dayPartCode(){
  return _dayPartCode;
}
void WeatherState::dayPartCode_set(int p){
  this->_dayPartCode = p;
}
bool WeatherState::dayPartCode_changed(){
  return this->_dayPartCode_changed;
}
void WeatherState::dayPartCode_changed_set(bool changed){
  this->_dayPartCode_changed = changed;
}
//--------------------
double WeatherState::tempF(){
  return _tempF;
}
void WeatherState::tempF_set(double p){
  this->_tempF = p;
}
bool WeatherState::tempF_changed(){
  return _tempF_changed;
}
void WeatherState::tempF_changed_set(bool changed){
  this->_tempF_changed = changed;
}
//--------------------
bool WeatherState::bSevere(){
  return _bSevere;
}
void WeatherState::bSevere_set(bool p){
  this->_bSevere = p;
}
bool WeatherState::bSevere_changed(){
  return _bSevere_changed;
}
void WeatherState::bSevere_changed_set(bool changed){
  this->_bSevere_changed = changed;
}
//--------------------
int WeatherState::wxAlertLevel(){
  return _wxAlertLevel;
}
void WeatherState::wxAlertLevel_set(int p){
  this->_wxAlertLevel = p;
}
bool WeatherState::wxAlertLevel_changed(){
  return _wxAlertLevel_changed;
}
void WeatherState::wxAlertLevel_changed_set(bool changed){
  this->_wxAlertLevel_changed = changed;
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
bool WeatherState::skyCode_changed(){
  return _skyCode_changed;
}
void WeatherState::skyCode_changed_set(bool changed){
  this->_skyCode_changed = changed;
}
//--------------------
int WeatherState::wxEnergy(){
  return _wxEnergy;
}
void WeatherState::wxEnergy_set(int p){
  this->_wxEnergy = p;
}
bool WeatherState::wxEnergy_changed(){
  return _wxEnergy_changed;
}
void WeatherState::wxEnergy_changed_set(bool changed){
  this->_wxEnergy_changed = changed;
}
//--------------------
int WeatherState::wxCode(){
  return _wxCode;
}
void WeatherState::wxCode_set(int p){
  this->_wxCode = p;
}
bool WeatherState::wxCode_changed(){
  return _wxCode_changed;
}
void WeatherState::wxCode_changed_set(bool changed){
  this->_wxCode_changed = changed;
}
//--------------------
bool WeatherState::bThunder(){
  return _bThunder;
}
void WeatherState::bThunder_set(bool p){
  this->_bThunder = p;
}
bool WeatherState::bThunder_changed(){
  return _bThunder_changed;
}
void WeatherState::bThunder_changed_set(bool changed){
  this->_bThunder_changed = changed;
}
//--------------------
bool WeatherState::bTornado(){
  return _bTornado;
}
void WeatherState::bTornado_set(bool p){
  this->_bTornado = p;
}
bool WeatherState::bTornado_changed(){
  return _bTornado_changed;
}
void WeatherState::bTornado_changed_set(bool changed){
  this->_bTornado_changed = changed;
}
//--------------------
int WeatherState::ledEffectIndex(){
  return _ledEffectIndex;
}
void WeatherState::ledEffectIndex_set(int p){
  this->_ledEffectIndex = p;
}
//--------------------
int WeatherState::ledBrightness(){
  return _ledBrightness;
}
void WeatherState::ledBrightness_set(int p){
  this->_ledBrightness = p;
}
//--------------------
int WeatherState::sfxIndex(){
  return _sfxIndex;
}
void WeatherState::sfxIndex_set(int p){
  this->_sfxIndex = p;
}
//--------------------
int WeatherState::ledDelayMs(){
  return _ledDelayMs;
}
void WeatherState::ledDelayMs_set(int p){
  if (p < 2)
    this->_ledDelayMs = 2;
  else
    this->_ledDelayMs = p;
}
//--------------------
