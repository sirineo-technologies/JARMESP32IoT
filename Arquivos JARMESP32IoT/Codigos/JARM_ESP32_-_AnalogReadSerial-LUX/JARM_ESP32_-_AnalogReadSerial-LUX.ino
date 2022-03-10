/// inicio display
#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);


//Analog Input
//#define ANALOG_PIN_0 4 // POT1 BEESP MF
//int analog_value = 0;


//#define ANALOG_PIN_1 25 // POT2 BEESP MF
//int analog_value1 = 0;

//// temp36
//#define ANALOG_PIN_2 15 // POT2 BEESP MF
//int tmp36 = 0;

// ldr
#define ANALOG_PIN_3 32 // LDR JARM ESP32
int ldr = 0;

/*
// PMW LED  1
#define LED_PIN 2  //GPIO 5 LED WROOMBEE

int freq = 5000;
int ledChannel = 0;
int resolution = 8;
int dutyCycle = 0;

//// PMW LED   2
//#define LED_PIN2 19  //LED6 - led assoc  BEESP MF

int freq2 = 5000;
int ledChannel2 = 0;
int resolution2 = 8;
int dutyCycle2 = 0;

//para o temp
int freq3 = 5000;
int ledChannel3 = 0;
int resolution3 = 8;
int dutyCycle3 = 0; */


//para o ldr
int freq4 = 5000;
int ledChannel4 = 0;
int resolution4 = 8;
int dutyCycle4 = 0;


void setup()
{
  
   
  
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("BEESP-MF + WROOMBEE -  Analog IN/OUT Test");

  

/*
   //POT 1
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(LED_PIN, ledChannel);
  ledcWrite(ledChannel, dutyCycle);

  //POT 2
  ledcSetup(ledChannel2, freq2, resolution2);
  ledcAttachPin(LED_PIN2, ledChannel2);
  ledcWrite(ledChannel2, dutyCycle2);

  //temp
  ledcSetup(ledChannel3, freq3, resolution3);
 // ledcAttachPin(LED_PIN2, ledChannel2);
  ledcWrite(ledChannel3, dutyCycle2); */

   //ldr
  ledcSetup(ledChannel4, freq4, resolution4);
 // ledcAttachPin(LED_PIN2, ledChannel2);
  ledcWrite(ledChannel4, dutyCycle4);
  

  }

void loop()
{
  
  display.clear();

  /*
  //POT 1
  analog_value = analogRead(ANALOG_PIN_0);
  Serial.print("POT1=");
  Serial.println(analog_value);
  dutyCycle = map(analog_value, 0, 4095, 0, 255);
  ledcWrite(ledChannel, dutyCycle);
  //display.drawString(0,0, "POT1= " + analog_value);
  String pot1;
  pot1 = analog_value;
  display.drawString(0,0,"POT1= " + pot1);
  display.display();

   //POT 2
  analog_value1 = analogRead(ANALOG_PIN_1);
  Serial.print("POT2=");
  Serial.println(analog_value1);
  dutyCycle2 = map(analog_value1, 0, 4095, 0, 255);
  ledcWrite(ledChannel2, dutyCycle2);

  String pot2;
  pot2 = analog_value1;
  display.drawString(0,10,"POT2= " + pot2);
  display.display();

   //TMP36
  tmp36 = analogRead(ANALOG_PIN_2);
  Serial.print("temp=");
  Serial.println(tmp36);
  dutyCycle3 = map(tmp36, 0, 4095, 0, 255);
  ledcWrite(ledChannel3, dutyCycle3);

  String temp36D;
  float temperaturac;
  temperaturac = (float(analogRead(tmp36))*5/(4095))/0.01;
  
  temp36D = temperaturac;
  display.drawString(0,20,"TEMP= " + temp36D);
  display.display(); */
  

  //LDR
  ldr = analogRead(ANALOG_PIN_3);
  Serial.print("luminosidade=");
  Serial.println(ldr);
  dutyCycle4 = map(ldr, 0, 4095, 0, 255);
  ledcWrite(ledChannel4, dutyCycle4);

  String ldrD;
  ldrD =  ldr;
  display.drawString(0,10,"LUM= " + ldrD);
  display.display();
  
 
  delay(500);
}





