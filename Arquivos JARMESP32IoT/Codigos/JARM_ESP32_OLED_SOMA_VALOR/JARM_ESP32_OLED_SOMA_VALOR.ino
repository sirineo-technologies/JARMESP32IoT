
const int buttonPin = 35;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);


int bconta_push = 0;
int bstatus_anterior = 0;
int bstatus_atual = 0;
String novoV ;

 
void setup()
{

  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  display.init();
  
}

void loop()
{

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW) {
    // turn LED on:

  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(0,18," botao off");
//  display.drawString(0,18," PRES:");
 // display.drawString(0,32," ALT:");
  display.display();
 // Serial.println("off");
  
 
     
  } else {
    // turn LED off:

  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(0,18," botao on");
  display.fillCircle(120, 5, 5);
//  display.drawString(0,18," TEM:");
 // display.drawString(0,32," HUMI:");
  
  
 // Serial.println("on");

  bstatus_anterior = bconta_push++;
  bstatus_atual = bstatus_anterior;
  
   
  }

 // Serial.println(bstatus_atual);
  int val = bstatus_atual;
  novoV = String(val);
  display.drawString(0,48," valor:");
  display.drawString(50,48, novoV);
  display.display();
  // FIM PUSH BUTTON

   delay(150);
  
 
}
