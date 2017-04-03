/******************************************
  PURPOSE:  IT Project Management - Final Project 
  Created by: Izzan Dienurrahman added and edited from Rudy Schlaf for www.makecourse.com
  DATE:   2/4/2017
  Version: 1.2.1
  Type: RELEASE
*******************************************/

/*
 * Created by Izzan Dienurrahman | UI Computer Engineering Student, March 2017
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>
  /***********************************************/
  /***********WIFI SETUP VARIABLES***************/
  /*********************************************/
WiFiClient client;
const char* ssid = "wifi";
const char* password = "88888888";
const char* host = "192.168.100.4";
String data,data2,data3;

  /***********************************************/
  /******************WIFI UDP VARIABLES**********/
  /*********************************************/
WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[10];  // buffer for incoming packets
char  replyPacket[] = "Thank you for using S.A.S!";  // a reply string to send back
String sReceived;
  /***********************************************/
  /***********SERVO SETUP VARIABLES**************/
  /*********************************************/
#define slot 3 //# of parking slot available (depends on # of servo(s)), change it if you want.
Servo servo[slot]; //instantiate array of servo object depends on number of servo(s).
int servoPin; //Pin D3 WeMos IO/10k,Pull-up

  /***********************************************/
  /***********PARKING SETUP VARIABLES************/
  /*********************************************/
#define empty 24 //error code for full parking slot/empty bike
int i;
int parking[slot];
int pinServo[slot]={D8,D7,D6};
int svPin;
String checkborrow;
String checkreturn;
String terminal = "halte1"; //change this if you want another terminal
void setup()
{
  Serial.begin(9600);
  Serial.println();

  //WeMos built-in LED initiated as output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  //connect to sas_rfid access point
  WiFi.begin(ssid,password);
  
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("Connected to wifi");
  printWifiStatus();

  //begin udp service
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  //fill parking slot w/ reference to database
  //and init servo position (in degree angle) 
  fillSlot();
  setupDoneBlink();//blink sign of setup has been done 
}

void loop() 
{
  //show parking slot current status 
  showSlot();
  delay(1000);
  //find incoming packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    //copy incoming packet to string
    for (int j=0 ; j<sizeof incomingPacket ; j++) //copy the sTemp[] contents to sfinal
         {
           sReceived+=incomingPacket[j]; //copy to string sfinal char by char except zero value appended before. 
         }
    Serial.println("sReceived= " + sReceived);
    
    //check current parking slot status
    checkborrow=borrowCheck(); //check if there is any bike to borrow
    checkreturn=returnCheck(); //check if there is any slot to return to
    
    //Access remote server
    ledON();//status busy
    wifiClient();

//    //flush redundant data (if any)
//    Udp.flush();
    
    //clear string  
    sReceived="";
  }  
    ledOFF();//status idle
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
