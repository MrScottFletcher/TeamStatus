
#include <ArduinoJson.h>
Benoit Blanchon
5.13.1

 
#include <DHT.h>
DHT sensor librbary
Adafruit
1.3.8
  
  --NOT--
  DHT Sensor librbay for ESPx
  
#include <Adafruit_NeoPixel.h>
Adafruit Neopixel
Adafruit
1.3.5

#include <AzureIoTHub.h>
AzureIotHub
Microsoft
1.0.45

#include "AzureIoTUtility.h"
AzureIotUtility
Microsoft
1.0.45


#include <AzureIoTProtocol_MQTT.h>
AzureIoTProtocol_MQTT
Microsoft
1.0.45


#include <Adafruit_Sensor.h>
Adafruit Unified Sensor
Adafruit
1.1.2

-- required the following
Adafruit ADXL343


and AGAIN, with this error
 #include <DHT.h>
 so tried 1.2.1
 
 
 ..then commented out line 137
 of Arduino.h in 
 C:\Users\scott\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.5.1\cores\esp8266
 #define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
 
 
Then, my new code complained about the old Json 
DeserializationError' was not declared in this scope
so upgraded ArduinoJson.h
Benoit Blanchon
5.13.1  ->  6.15.0
 
******************
Don't open the Arduino IDE and the Visual Studio (with the Visual Micro Arduino extenion) at the same time. :)
"unable to create a folder to save the sketch: mkdir sketch: Access is denied.
Error compiling for board Adafruit Feather HUZZAH ESP8266.
******************

Then, I had trouble getting the serializeJson() call working with the new v6.0 stuff
"which is of non-class type 'char  
so I reverted back to the old ArduinoJson library version (per 6.0)
ArduinoJson.h
Benoit Blanchon
5.13.1  

Now I can use
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["deviceId"] = DEVICE_ID;
    root["messageId"] = messageId;
    root.printTo(payload, MESSAGE_MAX_LEN);
**********************

THEN I got this after finally connecting to the WiFi and using the correct IoT device connection string
"failure connecting to address MyHubNameHere.azure-devices.net.""

https://github.com/Azure/azure-iot-arduino/issues/89
"Arduino Core 2.5.0 and BearSSL are regarded as beta code but nonetheless Arduino IDE and Platform.io use them by default. 
Falling back to previos core version didn't fix the issue. 
My solution was to force the compiler to use axTLS (previous SSL library now regarded as deprecated in the new core)"

in sslClient_arduino.cpp  (C:\Users\yourUserName\Documents\Arduino\libraries\AzureIoTUtility\src\adapters):
#ifdef ARDUINO_ARCH_ESP8266
#define USING_AXTLS
#include "ESP8266WiFi.h"
//#include "WiFiClientSecure.h"
#include <WiFiClientSecureAxTLS.h>

using namespace axTLS;

static WiFiClientSecure sslClient; // for ESP8266
#elif ARDUINO_ARCH_ESP32


====================================
Add RotaryEncoder for the dial

Or try to use the Encoder Library, but the Arduiono core is old
I manually updated direct_pin_read.h and interrupt_pins.h from the head of this repo (utility folder) and now it compiles happily.
C:\Users\scott\Documents\Arduino\libraries\Encoder\utility
https://github.com/PaulStoffregen/Encoder/blob/master/utility/direct_pin_read.h
https://github.com/PaulStoffregen/Encoder/blob/master/utility/interrupt_pins.h

========================================

For the OLED display
Adafruit_GFX --- and all of the other requirements that it wants
Adafruit_SSD1306.h
--------------------------------------
edit the iothubtransport_mqtt_common.c file to comment out this nagging line.
LogError("Failure result from IoTHubMessage_GetData");

