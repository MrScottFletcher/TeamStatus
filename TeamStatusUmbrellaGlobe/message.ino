#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>

bool readMessage(int messageId, char* payload)
{
    Serial.println("readMessage() called");
    blinkLED();

    //float temperature = readTemperature();
    //float humidity = readHumidity();
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    //root["DeviceId"] = "";
    //root["messageId"] = messageId;
    
    //Note: test any sense values for NaN, and set to null if necessary
    //if (std::isnan(humidity))
    //    root["humidity"] = NULL;

    root.printTo(payload, MESSAGE_MAX_LEN);
    //return temperatureAlert;
    return false;
}

//void parseWeather(JsonObject *node){
//     //{"desired":{"ZipCode":"61614","tempF":61.2,"dayPart":0,"wxAlert":0,"wxSevere":false,"sky":4,"wx":0,"wxThndr":false...
//    //but on subsequent updates, it will only send the patched values, and will place them at the root
//    //{"tempF":61.2,"dayPart":0,"wxAlert":0,"wxSevere":false,"sky":4,"wx":0,"wxThndr":false...
//    return;
//}

void parseTwinMessage(char* message)
{
    //const size_t capacity = 9216; //(9K)

    double newTempF = -200;
    Serial.println("parseTwinMessage() called");
    blinkLED();

    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(message);
    if (!root.success())
    {
        Serial.printf("Parse %s failed.\r\n", message);
        return;
    }

    //On start, the server will send all properties
    //{"desired":{"ZipCode":"61614","tempF":61.2,"dayPart":0,"wxAlert":0,"wxSevere":false,"sky":4,"wx":0,"wxThndr":false...
    //but on subsequent updates, it will only send the patched values, and will place them at the root
    //{"tempF":61.2,"dayPart":0,"wxAlert":0,"wxSevere":false,"sky":4,"wx":0,"wxThndr":false...

    //Consider checking for 'desired', and passing that nested JsonObject at to the parser method

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

    if (root["desired"]["tempF"].success())
    {
        Serial.println("================");
        Serial.println("Parsing tempF from Desired:");
        updateWx.tempF_set(root["desired"]["tempF"]);
        Serial.println(updateWx.tempF());
        Serial.println("================");
        //parseWeather(root["desired"]);
        updateWx.zipCode_set(root["desired"]["ZipCode"]);
        updateWx.dayPartCode_set(root["desired"]["dayPart"]);
        updateWx.skyCode_set(root["desired"]["sky"]);
        updateWx.wxCode_set(root["desired"]["wx"]);
        updateWx.wxAlertLevel_set(root["desired"]["wxAlert"]);
        updateWx.bSevere_set(root["desired"]["wxSevere"]);
        updateWx.wxEnergy_set(root["desired"]["wxWow"]);
        updateWx.bThunder_set(root["desired"]["wxThndr"]);
        updateWx.bTornado_set(root["desired"]["wxTrndo"]);
    }
    else if (root.containsKey("tempF"))
    {
        Serial.println("================");
        Serial.println("Parsing tempF from ROOT:");
        updateWx.tempF_set(root["tempF"]);
        Serial.println(updateWx.tempF());
        Serial.println("================");
        updateWx.zipCode_set(root["ZipCode"]);
        updateWx.dayPartCode_set(root["dayPart"]);
        updateWx.skyCode_set(root["sky"]);
        updateWx.wxCode_set(root["wx"]);
        updateWx.wxAlertLevel_set(root["wxAlert"]);
        updateWx.bSevere_set(root["wxSevere"]);
        updateWx.wxEnergy_set(root["wxWow"]);
        updateWx.bThunder_set(root["wxThndr"]);
        updateWx.bTornado_set(root["wxTrndo"]);
        
        //do a method to set the LedEffectIndex.  Meanwhile, always use peaches
        //updateWx is global, so just succumb to the laziness....
    }
    else{
        Serial.println("================");
        Serial.println("Could not find tempF.  Sad.");
        Serial.println("================");
    }

    if(currentWx.IsDifferent(updateWx)){
      Serial.println("Difference detected");
      currentWx = updateWx;
      SetWeatherLedEffects();
      updateWeatherPending = true;
    }
    else{
      Serial.println("NO difference detected.  Boring.");
    }
}


//could we pass a WeatherState reference for updateWx?  sure.  Will we?  No. Cuz I not gud at C.
void SetWeatherLedEffects(){

  //dayPartCode
  //0 - //NIGHT
  //1 - //SUNRISE -- within x minutes of sunrise either way
  //2 - //DAYTIME
  //3 - //SUNSET -- within x minutes of sunset either way

  currentWx.ledEffectIndex_set(14); //CloudColors_p
  //Set silence
  currentWx.sfxIndex_set(-1);
  
  if(currentWx.dayPartCode() == 0){
    //dark
    currentWx.ledBrightness_set(30);
  }
  else if(currentWx.dayPartCode() == 2){
    currentWx.ledBrightness_set(150);
  }
  else{
    //is sunrise/sunset
    currentWx.ledEffectIndex_set(32); //PurpleOrange_p
    currentWx.ledBrightness_set(100);

    //birds
    //currentWx.sfxIndex_set(0);
  }

  switch (currentWx.wxCode()){
    case 0:   //0 - Clear
    case 1:   //1 - Clear
      //leave the non-severe weather codes in place//
      Serial.println("---Leaving WX CLEAR---");
    break;    
      break;
    case 2:   //2 - Thunderstorm
      currentWx.bThunder_set(true);
      currentWx.sfxIndex_set(SFX_16_THUNDER);
      Serial.println("---Setting WX THUNDER sound effect---");
      //keep falling through....
    case 3:   //3 - Drizzle
    case 4:   //4 - Rain - (wxCode 4 is not used?)
    case 5:   //5 - Rain
      currentWx.ledEffectIndex_set(24); //OceanColors_p
      Serial.println("---Setting RAIN Led effect---");
      break;
    case 6:   //6 - Snow
      currentWx.ledEffectIndex_set(14); //CloudColors_p
      //Cold wind would be good here?  Maybe very soft sleigh bells!
      //currentWx.sfxIndex_set(XXXX);
      Serial.println("---Setting WX SNOW---");
      break;
    case 7:    //7 - Atmosphere
      currentWx.ledEffectIndex_set(40);
      currentWx.sfxIndex_set(SFX_25_FOG_HORN_BARGE);
      Serial.println("---Setting WX FOG-ATMOSPHERE---");
      break;
    case 8:    //8 - Squalls
      currentWx.ledEffectIndex_set(39); //DeepReds_p
      //Better sound effect would be howling winds...
      currentWx.sfxIndex_set(SFX_16_THUNDER);
      Serial.println("---Setting WX SQUALLS---");
      break;
    case 9:    //9 - Tornado
      currentWx.ledEffectIndex_set(44); //RedBlue_p
      currentWx.sfxIndex_set(SFX_22_TORNADO_SIREN);
      currentWx.ledBrightness_set(250);
      currentWx.ledDelayMs_set(20);
      Serial.println("---Setting WX TORNADO from wxCode---");
      break;
  }

  //energy is wxEnergy - max of 1002 when energy is 0, min of 2 when energy is 10
  currentWx.ledDelayMs_set((1000) - (currentWx.wxEnergy() * 100) + 2); 
  currentWx.ledBrightness_set((currentWx.wxEnergy() * 20) + 40); 

  //===================================================================
  //Now, override the usual tree with specials - in ascending priority order...
  //===================================================================
  if(currentWx.bThunder()){
    //add some glitter for bThunder?  Add +1 becuase we planned ahead?
    currentWx.ledEffectIndex_set(currentWx.ledEffectIndex() + 1);
    Serial.println("---Thunder - Adding WX glitter for lightning ---");
  }
  //===================================================================
  //wxAlert values
  //0 = none, 1 = advisory, 2 = Watch, 3 = Warning
  
  Serial.printf("wxAlertLevel level: %i\r\n", currentWx.wxAlertLevel());
  Serial.printf("wx bSevere: %b\r\n", currentWx.bSevere());
  if(currentWx.bSevere()){
    Serial.println("---SEVERE indicated ---");
    //ignore advisories
    if(currentWx.wxAlertLevel() > 1 ){ 
        //WATCH
        currentWx.ledEffectIndex_set(44); //RedBlue_p
        currentWx.sfxIndex_set(SFX_19_EBS_INTERRUPT);
        currentWx.ledDelayMs_set(60);
        Serial.println("---Setting SEVERE alert---");
    }
    else if(currentWx.wxAlertLevel() > 2 ){ 
        //WARNING
        currentWx.ledEffectIndex_set(45); //RedBlue_p with glitter
        currentWx.sfxIndex_set(SFX_20_EAS_TONE);
        currentWx.ledBrightness_set(200);
        currentWx.ledDelayMs_set(40);
        Serial.println("---Setting SEVERE alert---");
    }
  }
  //===================================================================
  //bTornado?  If so, do the tornado thing - anything more to do here?
  if(currentWx.bTornado()){
      Serial.println("---TORNADO indicated ---");
      currentWx.ledEffectIndex_set(45); //RedBlue_p with Glitter
      currentWx.sfxIndex_set(SFX_22_TORNADO_SIREN);
      currentWx.ledBrightness_set(250);
      currentWx.ledDelayMs_set(20);
      Serial.println("---Setting WX TORNADO for bTornado flag ---");
  }
  //===================================================================
  
}

  //Could also do something with SkyCodes here
  //SkyCodes:
    //0 - Clear
    //1 - Few
    //2 - Scattered
    //3 - Broken
    //4 - Overcast  
