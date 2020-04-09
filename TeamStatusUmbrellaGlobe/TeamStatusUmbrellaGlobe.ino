// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       TeamStatusUmbrellaGlobe.ino
    Created:	4/4/2020 12:08:24 PM
    Author:     DESKTOP-62IO2EV\scott
*/


#include <Adafruit_NeoPixel.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>

#include "config.h"
#include "audioplayer.h"
#include "weather.h"

static bool messagePending = false;
static bool messageSending = true;

static char* connectionString;
static char* ssid;
static char* pass;
//static Adafruit_NeoPixel strip;

static int interval = INTERVAL;
static int fadeSpeed = FADE_SPEED;
static int fadePause = FADE_PAUSE;
static int red = RED;
static int green = GREEN;
static int blue = BLUE;
static bool lights = LIGHTS;
static bool flash = FLASH;

static IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    
    setupAudio(SFX_2_STARTUP_2);
    delay(1000);

    initNeoPixels();
    
    initSerial();
    
    readCredentials();
    delay(2000);
    
    initWifi();
    
    initTime();
    //initSensor();

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
        messageCount++;
        delay(interval);
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

    IoTHubClient_LL_DoWork(iotHubClientHandle);
    delay(interval);
}






void blinkLED()
{
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
}

void initNeoPixels()
{
    //strip = Adafruit_NeoPixel(NEO_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);

    //strip.begin();
    //strip.show(); // Initialize all pixels to 'off'
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


void fadeIn(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {

 /*   for (uint8_t b = 0; b < 255; b++) {
        for (uint8_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
        }
        strip.show();
        delay(wait);
    };*/
};

void fadeOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
    //for (uint8_t b = 255; b > 0; b--) {
    //    for (uint8_t i = 0; i < strip.numPixels(); i++) {
    //        strip.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
    //    }
    //    strip.show();
    //    delay(wait);
    //};

}

void setLights(uint8_t red, uint8_t green, uint8_t blue)
{
    //for (uint8_t i = 0; i < strip.numPixels(); i++) {
    //    strip.setPixelColor(i, red, green, blue);
    //}
    //strip.show();
}
