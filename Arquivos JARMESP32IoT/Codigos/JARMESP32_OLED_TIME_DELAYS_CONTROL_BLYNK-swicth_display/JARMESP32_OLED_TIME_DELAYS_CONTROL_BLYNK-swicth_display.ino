#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);

//switch tela time

String novoV;

const int sensorMin = 0;      // sensor minimum, discovered through experiment
const int sensorMax = 15;    // sensor maximum, discovered through experiment

const int LED=16; //define LED for Pin 9
void setup()
{
pinMode (LED, OUTPUT); //Set the LED pin as an output
Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.fillCircle(60, 10, 10);
  display.setFont(ArialMT_Plain_16);
  display.drawString(2, 25, "      SIRINEO");
  display.drawString(0, 40, "TECHNOLOGIES");
  display.display();
  delay(2000);
  display.clear();
}
void loop()
{
for (int i=0; i<=20; i=i+1)
{
digitalWrite(LED, HIGH);
delay(1000);
digitalWrite(LED, LOW);
delay(1000);

int range = map(i, sensorMin, sensorMax, 0, 3);
  
switch (range) {
    case 0:    // your hand is on the sensor
      novoV = String(i);
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," Valor tela 1:");
  display.drawString(50,40,novoV);
  display.display();
      break;
    case 1:    // your hand is close to the sensor
     novoV = String(i);
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," Tela 2:");
  display.drawString(50,40,novoV);
  display.display();
      break;
    case 2:    // your hand is a few inches from the sensor
    novoV = String(i);
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," Tela 3:");
  display.drawString(50,40,novoV);
  display.display();
      break;
    case 3:    // your hand is nowhere near the sensor
  novoV = String(i);
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," Tela 4:");
  display.drawString(50,40,novoV);
  display.display();
   break;
  }
   
} //fim for 






} //loop





