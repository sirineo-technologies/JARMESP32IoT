
//int delayt = 0;

int ledPin = 27;  // ligado ao led azul wroombee

#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
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

// the loop function runs over and over again forever
void loop() {

  int currentresult;

  for (int i = 0; i < 100; i++){
  //currentresult = mysoma(i,i+1);
  currentresult = mysoma(i,i);
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(currentresult);                       // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(currentresult); 
  Serial.println(currentresult);  

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2,"   JARM ESP32");
  display.drawString(10,23," BLYNK TIME");
  String voled = String(currentresult);
  display.drawString(40,40,voled + " s");
  display.display();
  
  }

                          // wait for a second
}

int mysoma(int m, int n){
  int result;
  result = m + n;
  return result;
  
}



