#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
//#include <DHT.h>
//#include <ArduinoJson\compatibility.hpp>


bool readMessage(int messageId, char* payload)
{
    //float temperature = readTemperature();
    //float humidity = readHumidity();
    //StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    //JsonObject& root = jsonBuffer.createObject();
    //root["deviceId"] = DEVICE_ID;
    //root["messageId"] = messageId;
    //bool temperatureAlert = false;

    //// NAN is not the valid json, change it to NULL
    //if (std::isnan(temperature))
    //{
    //    root["temperature"] = NULL;
    //}
    //else
    //{
    //    root["temperature"] = temperature;
    //    if (temperature > TEMPERATURE_ALERT)
    //    {
    //        temperatureAlert = true;
    //    }
    //}

    //if (std::isnan(humidity))
    //{
    //    root["humidity"] = NULL;
    //}
    //else
    //{
    //    root["humidity"] = humidity;
    //}
    //root.printTo(payload, MESSAGE_MAX_LEN);
    //return temperatureAlert;
    return false;
}

void parseTwinMessage(char* message)
{
    //const size_t capacity = 9216; //(9K)
    DynamicJsonDocument doc(MESSAGE_MAX_LEN);

    DeserializationError error = deserializeJson(doc, message);
    if (error)
    {
        String err = String(error.c_str());
        Serial.println(err);
        for (size_t i = 0; i < 5; i++)
        {
            //fadeIn(CRGB::Yellow, 10, 200);
            //delay(10000);
            //fadeOut(CRGB::Yellow, 10, 200);
        }
    }

    //JsonObject& root = jsonBuffer.pa.parseObject(message);
    //if (!root.success())
    //{
    //    Serial.printf("Parse %s failed.\r\n", message);
    //    return;
    //}

    //if (root["desired"]["interval"].success())
    //{
    //    interval = root["desired"]["interval"];
    //}
    //else if (root.containsKey("interval"))
    //{
    //    interval = root["interval"];
    //}

    //if (root["desired"]["lights"].success())
    //{
    //    lights = root["desired"]["lights"];
    //}
    //else if (root.containsKey("lights"))
    //{
    //    lights = root["lights"];
    //}

    //if (root["desired"]["fadeSpeed"].success())
    //{
    //    fadeSpeed = root["desired"]["fadeSpeed"];
    //}
    //else if (root.containsKey("fadeSpeed"))
    //{
    //    fadeSpeed = root["fadeSpeed"];
    //}

    //if (root["desired"]["red"].success())
    //{
    //    red = root["desired"]["red"];
    //}
    //else if (root.containsKey("red"))
    //{
    //    red = root["red"];
    //}

    //if (root["desired"]["green"].success())
    //{
    //    green = root["desired"]["green"];
    //}
    //else if (root.containsKey("green"))
    //{
    //    green = root["green"];
    //}

    //if (root["desired"]["blue"].success())
    //{
    //    blue = root["desired"]["blue"];
    //}
    //else if (root.containsKey("blue"))
    //{
    //    blue = root["blue"];
    //}

    //if (root["desired"]["flash"].success())
    //{
    //    flash = root["desired"]["flash"];
    //}
    //else if (root.containsKey("flash"))
    //{
    //    flash = root["flash"];
    //}

    //if (root["desired"]["fadePause"].success())
    //{
    //    fadePause = root["desired"]["fadePause"];
    //}
    //else if (root.containsKey("fadePause"))
    //{
    //    fadePause = root["fadePause"];
    //}

}
