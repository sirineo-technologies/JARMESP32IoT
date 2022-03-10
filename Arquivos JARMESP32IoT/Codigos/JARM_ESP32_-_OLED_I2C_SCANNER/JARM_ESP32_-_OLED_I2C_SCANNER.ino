// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    https://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, November 27, 2015.
//    Added waiting for the Leonardo serial communication.
//
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

/// inicio display

/*
  display oled 0.86  128 x 64 - 8192 pixels
  x->largura da tela 0-127
  y->altura da tela 0-63
  u8g.drawStr( x, y, "texto");

  pixel 0,0 -------------------- pixel 127,0
  |                                        |
  |                                        |
  |                                        |
  |                                        |
  |        128 x 64 - 8192 pixels          |
  |                                        |
  |                                        |
  |                                        |
  |                                        |
  pixel 0,63 ---------------------pixel 127,63

*/

#include <Wire.h>
#include "SSD1306.h" 
// Include the UI lib
#include "OLEDDisplayUi.h"

SSD1306  display(0x3c, 21, 22);

 
#include <Wire.h>

 
void setup()
{

   display.init();
   
   Wire.begin();
 
   Serial.begin(115200);
  while (!Serial);             // Leonardo: wait for serial monitor
   Serial.println("\nI2C Scanner");
}
 
 
void loop()
{
  
  byte error, address;
  int nDevices;
  int valor = 7;

  

   Serial.println("JARM ESP32 IOT - SiriNEO Technologies");
   Serial.println("Code: I2C Scanner");
   Serial.println("Scanning...");

  
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
       Serial.print("I2C "); 
       Serial.print(nDevices +1); 
       Serial.print(" device found at address 0x");

      
       
      if (address<16)
            
       Serial.print("0");
       Serial.print(address,HEX);
       Serial.println("  !");
          
       nDevices++;

       // display.clear(); comentado pois ele apagava cada valor novo no display
        
        display.flipScreenVertically();
        display.setFont(ArialMT_Plain_10);
        display.drawString(13,3,"SiriNEO Technologies");
        display.setFont(ArialMT_Plain_10);
        display.drawString(0,(valor+ (nDevices*10)),"ADDRESS FOUND:  0x " + (String(address,HEX)));
        display.display();
       
      // Serial.println(nDevices);
      /*
        for (int i = 0; i <= nDevices; i++) {

        display.clear();
        display.flipScreenVertically();
        display.setFont(ArialMT_Plain_10);
        display.drawString(13,3,"SiriNEO Technologies");
        display.setFont(ArialMT_Plain_10);
        display.drawString(0,(valor+nDevices),"ADDRESS FOUND:  0x " + (String(address,HEX)));
        display.display();  */
        
       }//fim for
                 
             
    else if (error==4)
    {
       Serial.print("Unknown error at address 0x");
      if (address<16)
         Serial.print("0");
       Serial.println(address,HEX);
    }  
  }

  if (nDevices == 0)
     Serial.println("No I2C devices found\n");
  else
     
     Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
  
} // fim loop



