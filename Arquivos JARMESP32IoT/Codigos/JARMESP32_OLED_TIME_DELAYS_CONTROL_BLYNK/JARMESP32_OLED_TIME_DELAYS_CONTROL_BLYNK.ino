#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);


String novoV;

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
for (int i=100; i<=1000; i=i+10)
{
digitalWrite(LED, HIGH);
delay(i);
digitalWrite(LED, LOW);
delay(i);

  novoV = String(i);
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," Valor Delay:");
  display.drawString(50,40,novoV);
  display.display();

}
}





