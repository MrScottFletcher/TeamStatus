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

    Serial.println("================");
    Serial.println("Parsing tempF:");

    tempF = root["desired"]["tempF"];

    Serial.println("SUCCESS!  Yay");
    Serial.println(tempF);
    Serial.println("Printed TempF");
    Serial.println("================");
}
