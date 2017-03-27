#include <ESP8266WiFi.h>

const char* ssid = "wifi";
const char* password = "88888888";

const char* host = "192.168.100.4";
String data;

int npm= 1406531952;
void setup()
{
  Serial.begin(115200);
  Serial.println();
  //================================================WEMOS BUILTIN LED PIN as OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);                 
  //================================================WIFI DEFINITION
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  //================================================END OF DEFINTION
}


void loop()
{
  WiFiClient client;
  
  Serial.printf("\n[Connecting to %s ... ", host);
  
  
  if (client.connect(host, 80))
  {
    Serial.println("connected]");
    Serial.println("[Sending a request]");
 
    data = "npm=" + (String)npm;
 
    client.println("POST /wemos_php/add.php HTTP/1.1"); 
    client.println("Host: 192.168.100.4"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: ");
    client.println(data.length()); 
    client.println(); 
    client.print(data);

    Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {       
        String line = client.readStringUntil('\n'); //read string line per line
        
        if(line=="end of preamble"){                //do this routine if line says "end of preamble"
            Serial.println(line);                   //printout the line "end of preamble"
            int response = client.read();           //read the next important byte
            Serial.println(response);               //printout the response from php file.      
            if(response==49){                       //if response = 1 (49 in ASCII) do blinkLED
                blinkLED();
              }
            else if (response==-1){                 //invalid npm or student not valid anymore
                blinkLED2();
                blinkLED2();
              }
            else{                                   
                blinkLED2();                        //else SQL query error
                blinkLED2();
                blinkLED2();
                blinkLED2();
              }
            client.flush();                         //flush buffer so it exits the while loop.
          }
         else{
            Serial.println(line);                   //if preamble not yet ended, print that line.  
          }
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(500);
}

void blinkLED(){
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(3000);                       // wait for a second
    digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
    delay(3000);                       // wait for a second
  }

void blinkLED2(){
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
    delay(500);                       // wait for a second
  }
