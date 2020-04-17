#define SFX_1_STARTUP 1
#define SFX_2_STARTUP_2 2
#define SFX_3_CARTOON_COMPUTER  3
#define SFX_10_DOORBELL  10
#define SFX_11_MORSE_CODE  11
#define SFX_12_MODEM_SOUNDS  12
#define SFX_13_FRONT_DESK_BELL  13
#define SFX_14_DIXIE_HORN  14
#define SFX_15_SUBMARINE_DIVING  15
#define SFX_16_GLASS_PING  16
#define SFX_100_THUNDER  100
#define SFX_101_THUNDER_STRIKE_2  101
#define SFX_102_THUNDER_STRIKE_1  102
#define SFX_103_EBS_INTERRUPT  103
#define SFX_104_EAS_TONE  104
#define SFX_105_ATTENTION_TORNADO_WARNING  105
#define SFX_106_TORNADO_SIREN  106
#define SFX_200_CAR_ALARM_CHIRPS  200
#define SFX_201_POLICE_SIREN_WHOOP_UP  201
#define SFX_202_FOG_HORN_BARGE  202
#define SFX_203_BIG_FAT_WARNING_ALARM  203
#define SFX_300_COMMON_FART  300
#define SFX_301_ONE_PERSON_CHEERING  301
#define SFX_400_PRODUCTION_SYSTEM_ALERT  400
#define SFX_401_PRODUCTION_WARNING  401
#define SFX_402_PRODUCTION_RESOLVED  402
#define SFX_500_UNABLE_TO_CONNECT_WIFI  500
#define SFX_501_WIFI_CONNNECTION_LOST  501
#define SFX_600_UNABLE_TO_REGISTER_IOT_SERVER  600

#define DFPLAYER_RX_PIN 26 // D5 //14
#define DFPLAYER_TX_PIN 27 //Cannot use 12 on ESP32 or it will boot over and over!!!// D6 //12

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(DFPLAYER_RX_PIN,DFPLAYER_TX_PIN); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


void setupAudio(int playConfirmSound)
{
  mySoftwareSerial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo (ESP SoftwareSerial)"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~10 seconds)"));


  //Use softwareSerial to communicate with mp3.
  if (!myDFPlayer.begin(mySoftwareSerial)) 
  { 
    delay(10000);
    if (!myDFPlayer.begin(mySoftwareSerial)) 
    {  //Use softwareSerial to communicate with mp3.
      Serial.println(F("Unable to begin (after 10 sec retry):"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
      while(true);
    }
  }
  
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(15);  //Set volume value (0~30).
  myDFPlayer.volumeUp(); //Volume Up
  myDFPlayer.volumeDown(); //Volume Down
  
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

  if(playConfirmSound > 0)
  {
    myDFPlayer.play(playConfirmSound);
  }
}

//###################################################################################
void play_WifiConnected(){
  myDFPlayer.play(SFX_2_STARTUP_2);
}

void play_WifiDisconnected(){
  myDFPlayer.play(SFX_501_WIFI_CONNNECTION_LOST);
}

void play_IoT_HubConnectionFailure(){
  myDFPlayer.play(SFX_600_UNABLE_TO_REGISTER_IOT_SERVER);
}

//------------------------------------
void play_SysMonitor_Alert(){
  myDFPlayer.play(SFX_400_PRODUCTION_SYSTEM_ALERT);
}

void play_SysMonitor_Warning(){
  myDFPlayer.play(SFX_401_PRODUCTION_WARNING);
}

void play_SysMonitor_Resolved(){
  myDFPlayer.play(SFX_402_PRODUCTION_RESOLVED);
  delay(2000);
  myDFPlayer.play(SFX_301_ONE_PERSON_CHEERING);
}

//------------------------------------
void play_Notice_Bell(){
  myDFPlayer.play(SFX_13_FRONT_DESK_BELL);
}

void play_Notice_Bell2(){
  myDFPlayer.play(SFX_16_GLASS_PING);
}

void play_Notice_MorseCode(){
  myDFPlayer.play(SFX_11_MORSE_CODE);
}

//-----------------------------------------
void play_Weather_Thunder(){
  //randomize thunder or something?
  myDFPlayer.play(SFX_100_THUNDER);
  //myDFPlayer.play(SFX_101_THUNDER_STRIKE_2);
  //myDFPlayer.play(SFX_102_THUNDER_STRIKE_1);
}

void play_Weather_Advisory(){
  myDFPlayer.play(SFX_200_CAR_ALARM_CHIRPS);
}

void play_Weather_Watch(){
  myDFPlayer.play(SFX_103_EBS_INTERRUPT);
}

void play_Weather_Warning(){
  myDFPlayer.play(SFX_104_EAS_TONE);
}

void play_Weather_Tornado_Warning(){
  myDFPlayer.play(SFX_105_ATTENTION_TORNADO_WARNING);
}

void play_Weather_Tornado_CurrentCondition(){
  myDFPlayer.play(SFX_106_TORNADO_SIREN);
}

void play_Weather_Fog(){
  myDFPlayer.play(SFX_202_FOG_HORN_BARGE);
}
//-----------------------------------------


//###################################################################################
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

  //----Set different EQ----
  //myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
//  myDFPlayer.EQ(DFPLAYER_EQ_POP);
//  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
//  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
//  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
//  myDFPlayer.EQ(DFPLAYER_EQ_BASS);
  
  //----Set device we use SD as default----
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_U_DISK);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_AUX);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SLEEP);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_FLASH);
  
  //----Mp3 control----
//  myDFPlayer.sleep();     //sleep
//  myDFPlayer.reset();     //Reset the module
//  myDFPlayer.enableDAC();  //Enable On-chip DAC
//  myDFPlayer.disableDAC();  //Disable On-chip DAC
//  myDFPlayer.outputSetting(true, 15); //output setting, enable the output and set the gain to 15
  
  //----Mp3 play----
//  myDFPlayer.next();  //Play next mp3
//  delay(1000);
//  myDFPlayer.previous();  //Play previous mp3
//  delay(1000);
//  myDFPlayer.play(1);  //Play the first mp3
//  delay(1000);
//  myDFPlayer.loop(1);  //Loop the first mp3
//  delay(1000);
//  myDFPlayer.pause();  //pause the mp3
//  delay(1000);
//  myDFPlayer.start();  //start the mp3 from the pause
//  delay(1000);
//  myDFPlayer.playFolder(15, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
//  delay(1000);
//  myDFPlayer.enableLoopAll(); //loop all mp3 files.
//  delay(1000);
//  myDFPlayer.disableLoopAll(); //stop loop all mp3 files.
//  delay(1000);
//  myDFPlayer.playMp3Folder(4); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
//  delay(1000);
//  myDFPlayer.advertise(3); //advertise specific mp3 in SD:/ADVERT/0003.mp3; File Name(0~65535)
//  delay(1000);
//  myDFPlayer.stopAdvertise(); //stop advertise
//  delay(1000);
//  myDFPlayer.playLargeFolder(2, 999); //play specific mp3 in SD:/02/004.mp3; Folder Name(1~10); File Name(1~1000)
//  delay(1000);
//  myDFPlayer.loopFolder(5); //loop all mp3 files in folder SD:/05.
//  delay(1000);
//  myDFPlayer.randomAll(); //Random play all the mp3.
//  delay(1000);
//  myDFPlayer.enableLoop(); //enable loop.
//  delay(1000);
//  myDFPlayer.disableLoop(); //disable loop.
//  delay(1000);
//
//  //----Read imformation----
//  Serial.println(myDFPlayer.readState()); //read mp3 state
//  Serial.println(myDFPlayer.readVolume()); //read current volume
//  Serial.println(myDFPlayer.readEQ()); //read EQ setting
//  Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
//  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
//  Serial.println(myDFPlayer.readFileCountsInFolder(3)); //read file counts in folder SD:/03
