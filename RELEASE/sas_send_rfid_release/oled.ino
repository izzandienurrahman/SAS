/*
 * @Author: Izzan Dienurrahman
 * @Since: 5 April 2017
 * Version: 1.0
 */

void sysReady(){
  oled.clear(PAGE); // Clear the display's internal memory
  oled.setFontType(1);  // Set the text to large (5 columns, 1 row worth of characters).
  oled.setCursor(0, 8);  // Set the text cursor to the upper-left of the screen.
  oled.print("System Ready"); // Print a const string
  oled.display(); // Draw to the screen
}

void conServer(){
  oled.clear(PAGE); // Clear the display's internal memory
  oled.setFontType(0);  // Set the text to large (5 columns, 1 row worth of characters).
  oled.setCursor(0,16);  // Set the text cursor to the upper-left of the screen.
  oled.print("Contacting server..."); // Print a const string
  oled.display(); // Draw to the screen
}

void noRespond(){
  oled.setFontType(0);  // Set the text to large (5 columns, 1 row worth of characters).
  oled.setCursor(0,32);  // Set the text cursor to the upper-left of the screen.
  oled.print("No respond"); // Print a const string
  oled.display(); // Draw to the screen
}

void authorized(){
  oled.setFontType(0);  // Set the text to large (5 columns, 1 row worth of characters).
  oled.setCursor(0,32);  // Set the text cursor to the upper-left of the screen.
  oled.print("Authorized"); // Print a const string
  oled.display(); // Draw to the screen
}

void plsRemove(){
  oled.clear(PAGE); // Clear the display's internal memory
  oled.setFontType(1);  // Set the text to large (5 columns, 1 row worth of characters).
  oled.setCursor(0,0);
  oled.print("Please remove ur card");
  oled.display(); // Draw to the screen
}

void thankYou(){
  oled.clear(PAGE); // Clear the display's internal memory
  oled.setFontType(0);  // Set the text to large (5 columns, 1 row worth of characters).
  oled.setCursor(0,0);  // Set the text cursor to the upper-left of the screen.
  oled.print("Thank you for using"); // Print a const string
  oled.setFontType(1);
  oled.setCursor(18,18);
  oled.print("SAS");
  oled.setFontType(0);
  oled.setCursor(0,32);
  oled.print("Have a");
  oled.setCursor(0,39);
  oled.print("great day!");
  oled.display(); // Draw to the screen
}

