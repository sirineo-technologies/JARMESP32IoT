//https://lastminuteengineers.com/oled-display-esp32-tutorial/

#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);


void setup() {
  
  Serial.begin(115200);
  // tela splash
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
 // display.drawString(0, 0, "  JARM ESP32 IOT");
  display.fillCircle(60, 10, 10);
  display.setFont(ArialMT_Plain_16);
  display.drawString(2, 20, "      SIRINEO");
  display.drawString(0, 35, "TECHNOLOGIES");
  display.display();
  delay(2000);
  display.clear();

}

void loop() {
 
 display.setFont(ArialMT_Plain_16);
//  display.setTextColor(BLACK, WHITE);
  display.drawHorizontalLine(0, 1, 127);
  display.drawHorizontalLine(0, 2, 127);
  display.drawHorizontalLine(0, 3, 127);
  display.drawString(0,5," TESTE DISPLAY");
  //display.drawString(0,10, lastStringLength.toString());
  //display.drawString(23,20,hora.toString());
  // display.drawHorizontalLine(distanciaH,distanciaV, caractere);
  display.drawHorizontalLine(0, 25, 127);
  display.drawHorizontalLine(0, 26, 127);
  display.drawHorizontalLine(0, 27, 127);
 // display.drawVerticalLine(0, 29, 30); //desenha uma linha vertical
  //display.drawVerticalLine(0, 30, 10);
 // display.drawVerticalLine(0, 31, 10);
 // display.drawRect(0, 31, 20,30); //desenha retangulo 20-> horizontal 30-> vertical
  display.drawRect(0, 31, 127,30); //desenha retangulo 20-> horizontal 30-> vertical
  display.drawRect(3, 33, 120,25); //desenha retangulo 20-> horizontal 30-> vertical
  //desenha circulo
  // display.drawCircle(thisSensor, 45, 10); //desenha circulo 20-> horizontal 30-> vertical
  // Serial.println(mov);
 // display.fillCircle(40, 45, 10); //desenha circulo 20-> horizontal 30-> vertical
  //display.drawCircle(95, 45, 10); //desenha circulo 20-> horizontal 30-> vertical
  display.display();
/*
   for (int i = 15; i <110; i++) {
    display.fillCircle(i, 45, 10); //desenha circulo 20-> horizontal 30-> vertical
    display.display();
    display.clear();
    Serial.println(i);
    delay(100);
  }*/

   int   L = 127;
  for (int i= 0; i < L ; i++) {
                for (int j = 0 ; j < 64; j++) {
                 display.fillCircle(i, j, 20); //desenha circulo 20-> horizontal 30-> vertical
                 display.display();
                 display.clear();
                 Serial.println(i);
                 Serial.println(j);
                 delay(10);
                }
  }
  
}
