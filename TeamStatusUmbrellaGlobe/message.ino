#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
//#include <DHT.h>
//#include <ArduinoJson\compatibility.hpp>


bool readMessage(int messageId, char* payload)
{
    Serial.println("readMessage() called");
    blinkLED();

    //float temperature = readTemperature();
    //float humidity = readHumidity();
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["DeviceId"] = DEVICE_ID;
    //root["messageId"] = messageId;
    
    //Note: test any sense values for NaN, and set to null if necessary
    //if (std::isnan(humidity))
    //    root["humidity"] = NULL;

    root.printTo(payload, MESSAGE_MAX_LEN);
    //return temperatureAlert;
    return false;
}

void parseTwinMessage(char* message)
{
    //const size_t capacity = 9216; //(9K)

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
//    Serial.println("================");
//    Serial.println("Parsing tempF:");
//
//    tempF = root["desired"]["tempF"];
//    if(tempF == 0)
//    {
//        tempF = root["tempF"];
//    }
//
//    Serial.println("SUCCESS!  Yay");
//    Serial.println(tempF);
//    Serial.println("Printed TempF");
//    Serial.println("================");

    if (root["desired"]["tempF"].success())
    {
        Serial.println("================");
        Serial.println("Parsing tempF from Desired:");
        tempF = root["desired"]["tempF"];
        Serial.println(tempF);
        Serial.println("================");
    }
    else if (root.containsKey("tempF"))
    {
        Serial.println("================");
        Serial.println("Parsing tempF from ROOT:");
        tempF = root["tempF"];
        Serial.println(tempF);
        Serial.println("================");
    }
    else{
        Serial.println("================");
        Serial.println("Could not find tempF.  Sad.");
        Serial.println("================");
    }
}
