
static int interval = INTERVAL;
static int fadeSpeed = FADE_SPEED;
static int fadePause = FADE_PAUSE;
static int red = RED;
static int green = GREEN;
static int blue = BLUE;
static bool lights = LIGHTS;
static bool flash = FLASH;


static Adafruit_NeoPixel strip;

void initNeoPixels()
{
    strip = Adafruit_NeoPixel(NEO_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);

    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}


void fadeIn(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {

    for (uint8_t b = 0; b < 255; b++) {
        for (uint8_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
        }
        strip.show();
        delay(wait);
    };
};

void fadeOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
    for (uint8_t b = 255; b > 0; b--) {
        for (uint8_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
        }
        strip.show();
        delay(wait);
    };

}

void setLights(uint8_t red, uint8_t green, uint8_t blue)
{
    for (uint8_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, red, green, blue);
    }
    strip.show();
}
