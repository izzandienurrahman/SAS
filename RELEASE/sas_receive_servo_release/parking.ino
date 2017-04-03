/**
*@Author Izzan Dienurrahman
*@Since 3/7/2017
*@Version 1.4
*/

  /***********************************************/
  /***********PARKING FUNCTION ROUTINE***********/
  /*********************************************/
void fillSlot(){
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {    
    Serial.println("connected]");
    data = "terminal=" + terminal;
    client.println("POST /wemos_php/fill.php HTTP/1.1"); 
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
//        Serial.println(line);
        if(line=="breakpoint"){ //sentinel string
          String slotnum = client.readStringUntil('\n');
//          Serial.println("slot = "+slotnum);
          String slotstatus = client.readStringUntil('\n');
//          Serial.println("status = "+slotstatus);
          
          //fill parking slot with reference to database
          parking[slotnum.toInt()]=slotstatus.toInt(); 
        }
      }
    }
    //attach each servo on the appropriate WeMos pin
    for(i=0;i<slot;i++){
      servo[i].attach(pinServo[i]);
      servo[i].write(90); //initiate position (in degree angle)
    }
  }
}

void showSlot(){
    Serial.printf("\n\nList of available bike(s) : ");
    for(i=0;i<slot;i++){
        Serial.printf("[%d] ",parking[i]);
    }
}

void successMsg(){
    Serial.printf("\nAccess granted. Use bike No : %d",findAvailableBike()+1);
}

void tyMsg(){
    Serial.printf("\nAccess granted. Please return this bike to slot No: %d",findEmptySlot()+1);
}

void sryMsg(){
    Serial.println("Sorry, no more bike available...");
}

void noParkMsg(){
    Serial.println("Sorry, no more parking field. Please contact the parking warden.");
}

int findAvailableBike(){
    int i=0;
    while (parking[i]==0){
        i++;
        if(i==slot){
          return empty;
        }
    }
    return i;
}

int findEmptySlot(){
    int i=0;
    while (parking[i]!=0){
        i++;
        if(i==slot){
          return empty;
        }
    }
    return i;
}

int removeBike(int x){
    parking[x]=0;
}

int addBike(int x){
    parking[x]=x+1;
}

boolean borrowCheck(){
    i=findAvailableBike();
    if(i!=empty){
        svPin=i;
        return true;
    }
    else{
        return false;
    }
}

boolean borrowBike(){
    if(borrowCheck()){
      Serial.printf("\nSlot to borrow: %d",i);
      successMsg();
      removeBike(i);
      return true;
    }
    else{
      sryMsg();
      return false;
    }
}

boolean returnCheck(){
    i=findEmptySlot();
    if(i!=empty){
        svPin=i;
        return true;
    }
    else{
        return false;
    }
}

boolean returnBike(){
  if(returnCheck()){
    Serial.printf("\nSlot to return to: %d",i);
    tyMsg();
    addBike(i);
    return true;
  }
  else{
    noParkMsg();
    return false;
  }
}

void borrowRoutine(){
    if(borrowBike()){
      svUnlock(servo[svPin]);
      lockRoutine();
    }
}

void returnRoutine(){
    if(returnBike()){
      svUnlock(servo[svPin]);
      lockRoutine();    
    }
}

void lockRoutine(){
    delay(2000); //delay before servo is locked again
    svLock(servo[svPin]);
}

