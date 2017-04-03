/******************************************Blink the Builtin LED******************************************************/
void ledON(){
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on 
  }

void ledOFF(){
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage HIGH
}

void setupDoneBlink(){
  for(i=0;i<5;i++){
    ledON();
    delay(500);
    ledOFF();
    delay(500); 
  }
}
