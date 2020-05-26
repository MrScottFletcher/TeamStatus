#include <FastLED.h>

#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[LED_STRIP_NUMPIXELS];

static int loop_delay_ms = LED_LOOP_DELAY_MS;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;
int currentEffectIndex = 0;
int maxEffectsIndex = 45;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

bool glitterMode = false;

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < LED_STRIP_NUMPIXELS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        //colorIndex += 3;
        colorIndex += 1;
    }
}

//####################################################################################################################

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.


// Gradient palette "cw2_078_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/2/tn/cw2-078.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

DEFINE_GRADIENT_PALETTE( ReddishOrange_gp ) {
    0, 227, 69, 13,
  127, 206, 36, 22,
  255,  49,  9,  3};
CRGBPalette16 ReddishOrange_p = ReddishOrange_gp;

// Gradient palette "cw2_073_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/2/tn/cw2-073.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.
DEFINE_GRADIENT_PALETTE( PurpleOrange_gp ) {
    0,   7,  1, 10,
  127,  87,  7, 13,
  255, 150, 88, 16};
CRGBPalette16 PurpleOrange_p = PurpleOrange_gp;

// Gradient palette "cw2_073_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/2/tn/cw2-073.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.
DEFINE_GRADIENT_PALETTE( BlueLightBlue_gp ) {
    0,   7,  1, 10,
  127,  87,  7, 13,
  255, 150, 88, 16};
CRGBPalette16 BlueLightBlue_p = BlueLightBlue_gp;

  // Gradient palette "cw2_068_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/2/tn/cw2-068.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.
DEFINE_GRADIENT_PALETTE( DeepReds_gp ) {
    0,   2,  3,  9,
  127, 146,  5,  1,
  255, 232, 74,  9};
CRGBPalette16 DeepReds_p = DeepReds_gp;
  
// Gradient palette "cw2_081_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/2/tn/cw2-081.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.
DEFINE_GRADIENT_PALETTE( BlueGreens_gp ) {
    0,   1, 16, 52,
  127,  35, 32,138,
  255,  67,119, 23};
CRGBPalette16 BlueGreens_p = BlueGreens_gp;


// Gradient palette "cw2_060_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/2/tn/cw2-060.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.
DEFINE_GRADIENT_PALETTE( Peaches_gp ) {
    0, 100, 15,  1,
  127, 190, 60, 11,
  255, 244,131, 54};
CRGBPalette16 Peaches_p = Peaches_gp;

// Gradient palette "cw2_056_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/2/tn/cw2-056.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.
DEFINE_GRADIENT_PALETTE( LightPeaches_gp ) {
    0, 104, 90, 80,
  127, 203, 99, 46,
  255, 186,178, 56};
CRGBPalette16 LightPeaches_p = LightPeaches_gp;

// Gradient palette "cw2_056_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/2/tn/cw2-056.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.
DEFINE_GRADIENT_PALETTE( RedBlue_gp ) {
    0, 104, 90, 80,
  127, 203, 99, 46,
  255, 186,178, 56};
CRGBPalette16 RedBlue_p = RedBlue_gp;


// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.





// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};

void addGlitter( fract8 chanceOfGlitter) {
  if( random8() < chanceOfGlitter) {
    leds[ random16(LED_STRIP_NUMPIXELS) ] += CRGB::White;}
}

//####################################################################################################################



void SetCurrentEffect(uint8_t index){
  //using a switch instead of an array to do more modifcations
  Serial.printf("Set LED Cloud CurrentEffect index: %i.\r\n", index);
  glitterMode = false;
  switch(index){
        case 0:
        { currentPalette = RainbowColors_p;         Serial.println("RainbowColors_p");  currentBlending = LINEARBLEND;    break;}
        case 1:
        { currentPalette = RainbowColors_p;         glitterMode = true; Serial.println("RainbowColors_p GLITTER");  currentBlending = LINEARBLEND;    break;}
        case 2:
        { currentPalette = RainbowStripeColors_p;   Serial.println("RainbowStripeColors_p");  currentBlending = NOBLEND;  break;}
        case 3:
        { currentPalette = RainbowStripeColors_p;   glitterMode = true; Serial.println("RainbowStripeColors_p GLITTER");  currentBlending = NOBLEND;  break;}
        case 4:
        { currentPalette = RainbowStripeColors_p;   Serial.println("RainbowStripeColors_p Linear");  currentBlending = LINEARBLEND; break;}
        case 5:
        { currentPalette = RainbowStripeColors_p;   glitterMode = true; Serial.println("RainbowStripeColors_p Linear GLITTER");  currentBlending = LINEARBLEND; break;}
        case 6:
        { SetupPurpleAndGreenPalette();             Serial.println("SetupPurpleAndGreenPalette");  currentBlending = LINEARBLEND; break;}
        case 7:
        { SetupPurpleAndGreenPalette();             glitterMode = true; Serial.println("SetupPurpleAndGreenPalette GLITTER");  currentBlending = LINEARBLEND; break;}
        case 8:
        { SetupTotallyRandomPalette();              Serial.println("SetupTotallyRandomPalette");  currentBlending = LINEARBLEND; break;}
        case 9:
        { SetupTotallyRandomPalette();              glitterMode = true;  Serial.println("SetupTotallyRandomPalette GLITTER");  currentBlending = LINEARBLEND; break;}
        case 10:
        { SetupBlackAndWhiteStripedPalette();       Serial.println("SetupBlackAndWhiteStripedPalette");  currentBlending = NOBLEND; break;}
        case 11:
        { SetupBlackAndWhiteStripedPalette();       glitterMode = true; Serial.println("SetupBlackAndWhiteStripedPalette GLITTER");  currentBlending = NOBLEND; break;}
        case 12:
        { SetupBlackAndWhiteStripedPalette();       Serial.println("SetupBlackAndWhiteStripedPalette Linear");  currentBlending = LINEARBLEND; break;}
        case 13:
        { SetupBlackAndWhiteStripedPalette();       glitterMode = true; Serial.println("SetupBlackAndWhiteStripedPalette Linear GLITTER");  currentBlending = LINEARBLEND; break;}
        case 14:
        { currentPalette = CloudColors_p;           Serial.println("CloudColors_p");  currentBlending = LINEARBLEND; break;}
        case 15:
        { currentPalette = CloudColors_p;           glitterMode = true; Serial.println("CloudColors_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 16:
        { currentPalette = PartyColors_p;           Serial.println("PartyColors_p");  currentBlending = LINEARBLEND; break;}
        case 17:
        { currentPalette = PartyColors_p;           glitterMode = true; Serial.println("PartyColors_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 18:
        { currentPalette = myRedWhiteBluePalette_p; Serial.println("myRedWhiteBluePalette_p");  currentBlending = NOBLEND;  break;}
        case 19:
        { currentPalette = myRedWhiteBluePalette_p; glitterMode = true; Serial.println("myRedWhiteBluePalette_p GLITTER");  currentBlending = NOBLEND;  break;}
        case 20:
        { currentPalette = myRedWhiteBluePalette_p; Serial.println("myRedWhiteBluePalette_p Linear");  currentBlending = LINEARBLEND; break;}
        case 21:
        { currentPalette = myRedWhiteBluePalette_p; glitterMode = true; Serial.println("myRedWhiteBluePalette_p Linear GLITTER");  currentBlending = LINEARBLEND; break;}
        case 22:
        { currentPalette = LavaColors_p;            Serial.println("LavaColors_p");  currentBlending = LINEARBLEND; break;}
        case 23:
        { currentPalette = LavaColors_p;            glitterMode = true; Serial.println("LavaColors_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 24:
        { currentPalette = OceanColors_p;           Serial.println("OceanColors_p");  currentBlending = LINEARBLEND; break;}
        case 25:
        { currentPalette = OceanColors_p;           glitterMode = true; Serial.println("OceanColors_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 26:
        { currentPalette = ForestColors_p;          Serial.println("ForestColors_p");  currentBlending = LINEARBLEND; break;}
        case 27:
        { currentPalette = ForestColors_p;          glitterMode = true; Serial.println("ForestColors_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 28:
        { currentPalette = HeatColors_p;            Serial.println("HeatColors_p");  currentBlending = LINEARBLEND; break;}
        case 29:
        { currentPalette = HeatColors_p;            glitterMode = true; Serial.println("HeatColors_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 30:
        { currentPalette = ReddishOrange_p;            Serial.println("ReddishOrange_p");  currentBlending = LINEARBLEND; break;}
        case 31:
        { currentPalette = ReddishOrange_p;            glitterMode = true;Serial.println("ReddishOrange_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 32:
        { currentPalette = PurpleOrange_p;            Serial.println("PurpleOrange_p");  currentBlending = LINEARBLEND; break;}
        case 33:
        { currentPalette = PurpleOrange_p;            glitterMode = true;Serial.println("PurpleOrange_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 34:
        { currentPalette = BlueLightBlue_p;            Serial.println("BlueLightBlue_p");  currentBlending = LINEARBLEND; break;}
        case 35:
        { currentPalette = BlueLightBlue_p;            glitterMode = true;Serial.println("BlueLightBlue_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 36:
        { currentPalette = DeepReds_p;            Serial.println("DeepReds_p");  currentBlending = LINEARBLEND; break;}
        case 37:
        { currentPalette = DeepReds_p;            glitterMode = true;Serial.println("DeepReds_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 38:
        { currentPalette = BlueGreens_p;            Serial.println("BlueGreens_p");  currentBlending = LINEARBLEND; break;}
        case 39:
        { currentPalette = BlueGreens_p;            glitterMode = true;Serial.println("BlueGreens_pXXXXXX GLITTER");  currentBlending = LINEARBLEND; break;}
        case 40:
        { currentPalette = Peaches_p;            Serial.println("Peaches_p");  currentBlending = LINEARBLEND; break;}
        case 41:
        { currentPalette = Peaches_p;            glitterMode = true;Serial.println("Peaches_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 42:
        { currentPalette = LightPeaches_p;            Serial.println("LightPeaches_p");  currentBlending = LINEARBLEND; break;}
        case 43:
        { currentPalette = LightPeaches_p;            glitterMode = true;Serial.println("LightPeaches_p GLITTER");  currentBlending = LINEARBLEND; break;}
        case 44:
        { currentPalette = RedBlue_p;            Serial.println("RedBlue_p");  currentBlending = LINEARBLEND; break;}
        case 45:
        { currentPalette = RedBlue_p;            glitterMode = true;Serial.println("RedBlue_p GLITTER");  currentBlending = LINEARBLEND; break;}
//        case XX:
//        { currentPalette = XXXXXXXXXXXX;            Serial.println("XXXXXXXXX");  currentBlending = LINEARBLEND; break;}
//        case XX:
//        { currentPalette = XXXXXXXXXXXX;            glitterMode = true;Serial.println("XXXXXXXXX GLITTER");  currentBlending = LINEARBLEND; break;}
        default:{ break; }
        
  }
}

int ledEffectDelayMs = 0;

void SetCurrentLedDelayMs(uint8_t delayMs){
  //using a switch instead of an array to do more modifcations
  Serial.printf("Set LED Delay: %i.\r\n", delayMs);
  ledEffectDelayMs = delayMs;
}

void SetCurrentBrightness(uint8_t brightness){
  //using a switch instead of an array to do more modifcations
  Serial.printf("Set LED Brightness: %i.\r\n", brightness);
  FastLED.setBrightness(brightness);
}

void initFastLED(){
    FastLED.addLeds<LED_TYPE, LED_STRIP_DATA_PIN, COLOR_ORDER>(leds, LED_STRIP_NUMPIXELS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    currentEffectIndex = 42;
    ledEffectDelayMs = 100;
    SetCurrentEffect(currentEffectIndex);
}



void DoLEDLoopUpdate(){
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

    FillLEDsFromPaletteColors(startIndex);

    if(glitterMode){
      addGlitter(20);
      FastLED.show();
      FastLED.delay(20);
      FillLEDsFromPaletteColors(startIndex);
    }
    
    FastLED.show();
    FastLED.delay(ledEffectDelayMs);
}



void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         Serial.println("RainbowColors_p");  currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   Serial.println("RainbowStripeColors_p NoBlend");  currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   Serial.println("RainbowStripeColors_pLinearBlen");  currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             Serial.println("SetupPurpleAndGreenPalette");  currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              Serial.println("SetupTotallyRandomPalette");  currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       Serial.println("SetupBlackAndWhiteStripedPalette NoBlend");  currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       Serial.println("SetupBlackAndWhiteStripedPalette Linear");  currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           Serial.println("CloudColors_p");  currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           Serial.println("PartyColors_p");  currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; Serial.println("myRedWhiteBluePalette_p");  currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; Serial.println("myRedWhiteBluePalette_p");  currentBlending = LINEARBLEND; }
    }
}

//####################################################################################################################




















//void initNeoPixels()
//{
//    strip = Adafruit_NeoPixel(LED_STRIP_NUMPIXELS, LED_STRIP_DATA_PIN, NEO_GRB + NEO_KHZ800);
//
//    strip.begin();
//    strip.show(); // Initialize all pixels to 'off'
//}
//
//
//void fadeIn(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {
//
//    for (uint8_t b = 0; b < 255; b++) {
//        for (uint8_t i = 0; i < strip.numPixels(); i++) {
//            strip.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
//        }
//        strip.show();
//        delay(wait);
//    };
//};
//
//void fadeOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
//{
//    for (uint8_t b = 255; b > 0; b--) {
//        for (uint8_t i = 0; i < strip.numPixels(); i++) {
//            strip.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
//        }
//        strip.show();
//        delay(wait);
//    };
//
//}
//
//void setLights(uint8_t red, uint8_t green, uint8_t blue)
//{
//    for (uint8_t i = 0; i < strip.numPixels(); i++) {
//        strip.setPixelColor(i, red, green, blue);
//    }
//    strip.show();
//}
