/******************************************
  PURPOSE:  IT Project Management - Final Project 
  Created by: Izzan Dienurrahman added and edited from Rudy Schlaf for www.makecourse.com
  DATE:   5/4/2017
  Version: 1.4.1
  Type: RELEASE 
*******************************************/

/*
 * This sketch uses the MFRC522 Library to use RFID RC522 Module combined with WeMos D1 mini R2/D1 Mini Pro
 * The functions are documented in MFRC522.cpp.
 * Based on code by Miguel Balboa (circuitito.com), JEan, 2012.
 * Created by Izzan Dienurrahman | UI Computer Engineering Student, March 2017
*/
/****ESP8266****/
#include <ESP8266WiFi.h> //comment this if not needed
/****RFID****/
#include <MFRC522.h>//include the RFID reader library
/****UDP*****/
#include <WiFiUdp.h>
/****OLED****/
#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>
/****SPI****/
#include <SPI.h>//include the SPI bus library

#define SS_PIN D8  //slave select pin //10 for WeMos
#define RST_PIN D4  //reset pin //5 for WeMos

MFRC522 mfrc522(SS_PIN, RST_PIN);        // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;//create a MIFARE_Key struct named 'key', which will hold the card information

  /***********************************************/
  /***********OLED SETUP VARIABLES***************/
  /*********************************************/
#define PIN_RESET 255  //
#define DC_JUMPER 0  // I2C Addres: 0 - 0x3C, 1 - 0x3D
MicroOLED oled(PIN_RESET, DC_JUMPER);  // I2C Example
  /***********************************************/
  /***********RFID SETUP VARIABLES***************/
  /*********************************************/
int block=2;//this is the block number we will write into and then read. Do not write into 'sector trailer' block, since this can make the block unusable.
byte blockcontent[16] = {"1406577000"};//an array with 16 bytes to be written into one of the 64 card blocks is defined
//byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//all zeros. This can be used to delete a block.
byte readbackblock[18];//This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.
char sTemp[10];
String sfinal;
String sCheck;

  /***********************************************/
  /******************GENERAL VARIABLES***********/
  /*********************************************/
int i;//iterator
  /***********************************************/
  /******************WIFI UDP VARIABLES**********/
  /*********************************************/
//Object(s) instantiated
WiFiUDP Udp;
unsigned int remoteServoPort = 4210;
unsigned int localUdpPort = 4210;
char incomingPacket[255];  // buffer for incoming packets
const char* host = "192.168.100.10";
  /***********************************************/
  /***********WIFI SETUP VARIABLES***************/
  /*********************************************/
const char* ssid = "wifi";
const char* password = "88888888";
int maxtimeout = 20;
int timeout;
void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
  SPI.begin();               // Init SPI bus
  
  /***********************************************/
  /***************BEGIN OLED SETUP***************/
  /*********************************************/     
    // Before you can start using the OLED, call begin() to init
    // all of the pins and configure the OLED.
    oled.begin();
    oled.clear(PAGE); // Clear the display's internal memory
    oled.clear(ALL);  // Clear the library's display buffer
  
  /***********************************************/
  /***************BEGIN WIFI SETUP***************/
  /*********************************************/                 
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  //print wifi status
  printWifiStatus();

  //WeMos built-in LED initiated as output.
  pinMode(LED_BUILTIN, OUTPUT);

  /***********************************************/
  /***************RFID SETUP*********************/
  /*********************************************/ 
  //RFID sec.key for security purposes
  Serial.println("Scan a MIFARE Classic card");
  //Serial.println(sizeof sTemp); //uncomment this if u want to see student ID length +1;
  // Prepare the security key for the read and write functions - all six key bytes are set to 0xFF at chip delivery from the factory.
  // Since the cards in the kit are new and the keys were never defined, they are 0xFF
  // if we had a card that was programmed by someone else, we would need to know the key to be able to access it. This key would then need to be stored in 'key' instead.
 
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
        }
  //begin udp service
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop()
{ 
  sfinal=""; //clear string content for the next reading
  //initate RFID routine
  mfrc522.PCD_Init();        // Re-Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
        /*****************************************establishing contact with a tag/card**********************************************************************/ 
     //Look for new cards (in case you wonder what PICC means: proximity integrated circuit card)
  if ( ! mfrc522.PICC_IsNewCardPresent()) {//if PICC_IsNewCardPresent returns 1, a new card has been found and we continue
    Serial.println("Waiting for new card....");
    sysReady(); //display ready status on oled 
    delay(1000);
    return;//if it did not find a new card is returns a '0' and we return to the start of the loop
  }
  
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {//if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
    return;//if it returns a '0' something went wrong and we return to the start of the loop
  }
        // Among other things, the PICC_ReadCardSerial() method reads the UID and the SAK (Select acknowledge) into the mfrc522.uid struct, which is also instantiated
        // during this process.
        // The UID is needed during the authentication process
          //The Uid struct:
          //typedef struct {
    //byte    size;     // Number of bytes in the UID. 4, 7 or 10.
    //byte    uidByte[10];            //the user ID in 10 bytes.
    //byte    sak;      // The SAK (Select acknowledge) byte returned from the PICC after successful selection.
          //} Uid;
         
         Serial.println("Card selected");
         
         /*****************************************writing and reading a block on the card**********************************************************************/
         
   //writeBlock(block, blockcontent);//the blockcontent array is written into the card block
         //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
         
         //The 'PICC_DumpToSerial' method 'dumps' the entire MIFARE data block into the serial monitor. Very useful while programming a sketch with the RFID reader...
         //Notes:
         //(1) MIFARE cards conceal key A in all trailer blocks, and shows 0x00 instead of 0xFF. This is a secutiry feature. Key B appears to be public by default.
         //(2) The card needs to be on the reader for the entire duration of the dump. If it is removed prematurely, the dump interrupts and an error message will appear.
         //(3) The dump takes longer than the time alloted for interaction per pairing between reader and card, i.e. the readBlock function below will produce a timeout if
         //    the dump is used.
         
   //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));//uncomment this if you want to see the entire 1k memory with the block written into it.     
         
         readBlock(block, readbackblock);//read the block back
         Serial.print("read block: ");
         for (int j=0 ; j<16 ; j++)//print the block contents
         {
           Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
         }
         Serial.println("");
         
         memcpy(sTemp,readbackblock,sizeof sTemp);  //copy array of bytes to array of char sTemp[] with amount of size sTemp
         sTemp[sizeof sTemp] = '\0';                //append zero for string reading compatibility.            
         for (int j=0 ; j<sizeof sTemp ; j++) //copy the sTemp[] contents to sfinal
         {
           sfinal+=sTemp[j]; //copy to string sfinal char by char except zero value appended before. 
         }
         //Serial.println(sfinal); //uncomment this if you want to see the final string value
         Serial.println("");
         
         //relay RFID data via UDP
         Udp.beginPacket(host,remoteServoPort);
         Udp.write(sTemp);
         Udp.endPacket();
         conServer(); //display contacting server status
         Serial.print("Waiting ack packet");
         while(!Udp.parsePacket()){
          if(timeout==maxtimeout){
            timeout=0;//reset the timer
            noRespond();//display no respond status
            Serial.println("\nServer didn't respond, sorry :(");
            Serial.println("Please refrain from using S.A.S system for a while");
            noRespondBlink();//show no respond blink sign
            break;
          }
          else{
            Serial.print(".");
            ledON();
            delay(500);
            timeout++;
          }        
         }
         if(Udp.available()){
          timeout=0;//reset the timer
          authorized();//display authorized status from server
          Serial.println("ACK received!");
          thankYou();//display thank you from oled
          delay(2000);
          plsRemove();//display please remove the card
          Serial.println("Thank you for using SAS!");
          Serial.println("Please remove your card");
         }
         ledON();
         delay(3000);
}



