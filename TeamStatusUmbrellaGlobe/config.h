// Physical device information for board and sensor
//Don't need these...

// Pin layout configuration
#define ONBOARD_LED_PIN 2

#define LED_STRIP_DATA_PIN 19
#define LED_STRIP_NUMPIXELS 8
#define LED_LOOP_DELAY_MS 30

#define FADE_SPEED 10
#define FADE_PAUSE 10

//#define TEMPERATURE_ALERT 30

// Interval time(ms) for sending message to IoT Hub
#define MIN_IOT_MESSAGE_INTERVAL 2000
#define LIGHTS false 
#define FLASH false 

// EEPROM address configuration
#define EEPROM_SIZE 512

// SSID and SSID password's length should < 32 bytes
// http://serverfault.com/a/45509
#define SSID_LEN 32
#define PASS_LEN 32
#define CONNECTION_STRING_LEN 256

#define MESSAGE_MAX_LEN 256

#define WAKE_BUTTON_PIN 25
