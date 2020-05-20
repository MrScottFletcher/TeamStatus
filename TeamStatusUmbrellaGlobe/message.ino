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
        newTempF = root["desired"]["tempF"];
        Serial.println(newTempF);
        Serial.println("================");
        //parseWeather(root["desired"]);
        updateWx.zipCode_set(root["desired"]["ZipCode"]);
        updateWx.tempF_set(root["desired"]["tempF"]);
        updateWx.dayPartCode_set(root["desired"]["dayPart"]);
        updateWx.skyCode_set(root["desired"]["sky"]);
        updateWx.wxCode_set(root["desired"]["wx"]);
        updateWx.wxAlert_set(root["desired"]["wxAlert"]);
        updateWx.bSevere_set(root["desired"]["wxSevere"]);
        updateWx.wxEnergy_set(root["desired"]["wxWow"]);
        updateWx.bThunder_set(root["desired"]["wxThndr"]);
        updateWx.bTornado_set(root["desired"]["wxTrndo"]);

        //do a method to set the LedEffectIndex.  Meanwhile, always use peaches
        updateWx.ledEffectIndex_set(42);
        
    }
    else if (root.containsKey("tempF"))
    {
        Serial.println("================");
        Serial.println("Parsing tempF from ROOT:");
        newTempF = root["tempF"];
        Serial.println(newTempF);
        Serial.println("================");
        updateWx.zipCode_set(root["ZipCode"]);
        updateWx.tempF_set(root["tempF"]);
        updateWx.dayPartCode_set(root["dayPart"]);
        updateWx.skyCode_set(root["sky"]);
        updateWx.wxCode_set(root["wx"]);
        updateWx.wxAlert_set(root["wxAlert"]);
        updateWx.bSevere_set(root["wxSevere"]);
        updateWx.wxEnergy_set(root["wxWow"]);
        updateWx.bThunder_set(root["wxThndr"]);
        updateWx.bTornado_set(root["wxTrndo"]);
        
        //do a method to set the LedEffectIndex.  Meanwhile, always use peaches
        updateWx.ledEffectIndex_set(42);
    }
    else{
        Serial.println("================");
        Serial.println("Could not find tempF.  Sad.");
        Serial.println("================");
    }

    if(newTempF > -200 && newTempF != tempF){
      tempF = newTempF;
      currentWx = updateWx;
      updateWeatherPending = true;
    }
    if(currentWx.IsDifferent(updateWx)){
      currentWx = updateWx;
      updateWeatherPending = true;
    }
}
