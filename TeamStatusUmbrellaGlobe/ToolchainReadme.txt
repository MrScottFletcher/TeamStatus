
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
 unable to create a folder to save the sketch: mkdir sketch: Access is denied.
Error compiling for board Adafruit Feather HUZZAH ESP8266.
******************