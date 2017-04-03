/**
*@Author Izzan Dienurrahman (modified from sample instructables code)
*@Since 3/7/2017
*@Version 1.4
*/
  /***********************************************/
  /***********WIFI CLIENT FUNCTION ROUTINE*******/
  /*********************************************/
void wifiClient()
{
  ackPacket(); //send ack packet back to wemos rfid 
//  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  { 
//    Serial.println("connected]");
//    Serial.println("[Sending a request]");
//    Serial.println(checkborrow);
//    Serial.println(checkreturn);
    data = "npm=" + sReceived;
    data2= "&checkborrow=" + checkborrow;
    data3= "&checkreturn=" + checkreturn;
    data+=data2+data3;
    client.println("POST /wemos_php/system.php HTTP/1.1"); 
    client.println("Host: 192.168.100.4"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: ");
    client.println(data.length()); 
    client.println(); 
    client.print(data);

//    Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {       
        String line = client.readStringUntil('\n'); //read string line per line
        
        if(line=="end of preamble"){                //do this routine if line says "end of preamble"
//            Serial.println(line);                   //printout the line "end of preamble"
            String response = client.readStringUntil('\n');  //read the returned value from SQL query
            String username = client.readStringUntil('\n');           //read the returned value from SQL query
            String c_before = client.readStringUntil('\n');
            String c_after = client.readString();    
            if(response=="1"){                               //if response = 1 do blinkLED
//                Serial.println("Returned value: "+ response); //printout the response from php file.
//                Serial.println("Message: Hello "+ username);
//                Serial.println("Status `in_use` (before): "+ c_before); //status before 
//                Serial.println("Status `in_use` (after): "+ c_after); //status afer
                ledON();      //turn LED on
                if(c_before=="0"&&c_after=="1"){
                  borrowRoutine(); //run borrow bike routine
                  removeBike_db(String(svPin));  
                }
                else if(c_before=="1"&&c_after=="0"){
                  returnRoutine(); //run borrow bike routine
                  addBike_db(String(svPin));
                }
              }
            else if (response==""){   //invalid npm or student not valid anymore
//                Serial.println("Returned value: "+response + "[EMPTY]"); //printout the response from php file.
                for(int i=0;i<5;i++){
                  ledON();                                     
                  delay(500);
                  ledOFF();
                  delay(500); 
                }   
              }
            else{                                                                    
                for(int i=0;i<5;i++){
                  ledON();              //else SQL query error
                  delay(100);
                  ledOFF();
                  delay(100); 
                }   
              }
            client.flush();                         //flush buffer so it exits the while loop.
          }
         else{
            Serial.println(line);                   //if preamble not yet ended, print that line.  
          }
      }
    }
    ledOFF();   //Turn off LED
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    wifiClient();
  }
}

void ackPacket(){
    //send ack packet to wemos rfid 
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacket);
    Udp.endPacket();
}

