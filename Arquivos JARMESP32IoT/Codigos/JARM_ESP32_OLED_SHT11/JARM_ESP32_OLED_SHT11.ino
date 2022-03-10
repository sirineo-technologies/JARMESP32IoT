#include "DFRobot_SHT20.h"

#include <Wire.h>
#include "SSD1306.h"
// Include the UI lib
#include "OLEDDisplayUi.h"

#include <OneWire.h>
SSD1306 display(0x3c, 21, 22);
//SSD1306 display(0x78, 21, 22);

DFRobot_SHT20 sht20;

//#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);

String tempe;

void setup()
{
    
  display.init();
  display.flipScreenVertically();
 
  Serial.begin(115200);
  //delay(1000); // give me time to bring up serial monitor
  Serial.println("SHT20 - temp-umid Test");
    
   sht20.initSHT20(); // Init SHT20 Sensor
   // delay(100);
   sht20.checkSHT20(); // Check SHT20 Sensor

}

void loop()
{
    display.clear();
    
    float humd = sht20.readHumidity(); // Read Humidity
    float temp = sht20.readTemperature(); // Read Temperature
    Serial.print("Time:");
    Serial.print(millis());
    Serial.print(" Temperature:");
    Serial.print(temp, 1);
    Serial.print("C");
    Serial.print(" Humidity:");
    Serial.print(humd, 1);
    Serial.print("%");
    Serial.println();

    // ESCREVER OS DADOS DA TEMP
 

  String tempiC;
  tempiC = temp;
  String umid;
  umid = humd;

  
  //display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
  display.drawString(12,10,"SiriNEO Technologies");
// display.setFont(ArialMT_Plain_14);
  display.drawString(20,30,"TEMP-C= " + tempiC + " °C");
  display.drawString(20,40,"Umid= " + umid + " %");
  display.display();
    
    
    delay(800);
}
