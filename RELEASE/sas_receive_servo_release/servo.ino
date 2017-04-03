/**
*@Author Izzan Dienurrahman
*@Since 3/7/2017
*@Version 1.0.0
*/
  /***********************************************/
  /***********SERVO FUNCTION ROUTINE*************/
  /*********************************************/
void svLock(Servo servo) {
  servo.write(90);      //Define servo degree
  
}

void svUnlock(Servo servo) {
  servo.write(0);    //Define servo degree
}
