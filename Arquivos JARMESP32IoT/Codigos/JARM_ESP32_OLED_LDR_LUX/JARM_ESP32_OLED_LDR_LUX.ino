/// inicio display
#include <Wire.h>
#include "SSD1306.h" 
// Include the UI lib
#include "OLEDDisplayUi.h"

SSD1306  display(0x3c, 21, 22);



// ldr
#define ANALOG_PIN_3 32 // POT2 BEESP MF
int ldr = 0;


int freq = 5000;
int ledChannel = 0;
int resolution = 8;
int dutyCycle = 0;



//para o ldr
int freq4 = 5000;
int ledChannel4 = 0;
int resolution4 = 8;
int dutyCycle4 = 0;


void setup()
{
  
  display.init();
 
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("BEESP-MF + WROOMBEE -  Analog IN/OUT Test");


   //ldr
  ledcSetup(ledChannel4, freq4, resolution4);
 // ledcAttachPin(LED_PIN2, ledChannel2);
  ledcWrite(ledChannel4, dutyCycle4);
  

  }

void loop()
{
  
  display.clear();

   
  //LDR
  ldr = analogRead(ANALOG_PIN_3);
  Serial.print("luminosidade=");
  Serial.println(ldr);
  dutyCycle4 = map(ldr, 0, 4095, 0, 255);
  ledcWrite(ledChannel4, dutyCycle4);

  String ldrD;
  ldrD =  ldr;
  //display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.drawString(13,5,"SiriNEO Technologies");
  display.setFont(ArialMT_Plain_16);
  display.drawString(30,25,"LUM= " + ldrD);
  display.display();
  
 
  delay(500);
}
