// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       TeamStatusUmbrellaGlobe.ino
    Created:	4/4/2020 12:08:24 PM
    Author:     DESKTOP-62IO2EV\scott
*/


#include <Adafruit_NeoPixel.h>

#include <FastLED.h>
#include <Encoder.h>
//=======================================================================
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>

#include "config.h"
#include "audioplayer.h"
#include "weather.h"
#include "clouds.h"

static bool messagePending = false;
static bool messageSending = true;

static char* connectionString;
static char* ssid;
static char* pass;


static IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
     
    initSerial();
    delay(1000);
    
    setupAudio(SFX_2_STARTUP_2);
    delay(1000);

  //----------------------------------------------------------
  //Do these one by one until fail
    initNeoPixels();
        
    readCredentials();
    delay(1000);
    
    initWifi();
    fadeIn(100,100,100,5);
    delay(5000);
    fadeOut(0,100,0,5);
    
    initTime();

    iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);
    if (iotHubClientHandle == NULL)
    {
        Serial.println("Failed on IoTHubClient_CreateFromConnectionString.");
        play_IoT_HubConnectionFailure();
        while (1);
    }

    IoTHubClient_LL_SetOption(iotHubClientHandle, "product_info", "HappyPath_AdafruitFeatherHuzzah-C");
    IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, receiveMessageCallback, NULL);
    IoTHubClient_LL_SetDeviceMethodCallback(iotHubClientHandle, deviceMethodCallback, NULL);
    IoTHubClient_LL_SetDeviceTwinCallback(iotHubClientHandle, twinCallback, NULL);

    char messagePayload[MESSAGE_MAX_LEN];
    sendMessage(iotHubClientHandle, messagePayload);

}

static int messageCount = 1;
void loop()
{
    if (!messagePending && messageSending)
    {
        char messagePayload[MESSAGE_MAX_LEN];
        //to send a message.  This was the sample code for reading a temperature...
        //bool temperatureAlert = readMessage(messageCount, messagePayload);
        //sendMessage(iotHubClientHandle, messagePayload, temperatureAlert);
        //messageCount++;
        //delay(interval);
    }

//    if (lights)
//    {
//        Serial.println("Lights: True");
//        if (flash)
//        {
//            Serial.println("Lights: True and Flash");
//            fadeIn(red, green, blue, fadeSpeed);
//            delay(fadePause);
//            fadeOut(red, green, blue, fadeSpeed);
//        }
//        else
//        {
//            Serial.println("Lights: True no flash");
//            setLights(red, green, blue);
//        }
//    }
//    else
//    {
//        setLights(0, 0, 0);
//        Serial.println("Lights: False");
//    }

    //re-enable this
    IoTHubClient_LL_DoWork(iotHubClientHandle);
    
    delay(interval);
}






void blinkLED()
{
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
}



void initWifi()
{
    // Attempt to connect to Wifi network:
    Serial.printf("Attempting to connect to SSID: %s.\r\n", ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        // Get Mac Address and show it.
        // WiFi.macAddress(mac) save the mac address into a six length array, but the endian may be different. The huzzah board should
        // start from mac[0] to mac[5], but some other kinds of board run in the oppsite direction.
        uint8_t mac[6];
        WiFi.macAddress(mac);
        Serial.printf("You device with MAC address %02x:%02x:%02x:%02x:%02x:%02x connects to %s failed! Waiting 10 seconds to retry.\r\n",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], ssid);
        WiFi.begin(ssid, pass);
        delay(10000);
    }
    Serial.printf("Connected to wifi %s.\r\n", ssid);
}

void initTime()
{
    time_t epochTime;
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    delay(1000);
    while (true)
    {
        epochTime = time(NULL);

        if (epochTime == 0)
        {
            Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
            delay(2000);
        }
        else
        {
            Serial.printf("Fetched NTP epoch time is: %lu.\r\n", epochTime);
            break;
        }
    }
}
