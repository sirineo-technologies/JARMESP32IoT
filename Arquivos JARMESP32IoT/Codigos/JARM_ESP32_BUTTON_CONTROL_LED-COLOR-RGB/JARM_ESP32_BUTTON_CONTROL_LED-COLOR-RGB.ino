const int BLED=17; //Blue LED on Pin 9
const int GLED=27; //Green LED on Pin 10
const int RLED=16; //Red LED on Pin 11
const int BUTTON=35; //The Button is connected to pin 2
boolean lastButton = LOW; //Last Button State
boolean currentButton = LOW; //Current Button State
int ledMode = 0; //Cycle between LED states

#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);

void setup()
{
pinMode (BLED, OUTPUT); //Set Blue LED as Output
pinMode (GLED, OUTPUT); //Set Green LED as Output
pinMode (RLED, OUTPUT); //Set Red LED as Output
pinMode (BUTTON, INPUT); //Set button as input (not required)


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

/*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state.
*/
boolean debounce(boolean last)
{
boolean current = digitalRead(BUTTON); //Read the button state
if (last != current) //if it's different...
{
delay(5); //wait 5ms
current = digitalRead(BUTTON); //read it again
}
return current; //return the current value
}
/*
* LED Mode Selection
* Pass a number for the LED state and set it accordingly.
*/
void setMode(int mode)
{
//RED
if (mode == 1)
{
digitalWrite(RLED, HIGH);
digitalWrite(GLED, LOW);
digitalWrite(BLED, LOW);

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," RGBBRAN1");
  display.drawString(50,40,"MOD1");
  display.display();

}
//GREEN
else if (mode == 2)
{
digitalWrite(RLED, LOW);
digitalWrite(GLED, HIGH);
digitalWrite(BLED, LOW);

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," RGBBRAN2");
  display.drawString(50,40,"MOD2");
  display.display();

}
//BLUE
else if (mode == 3)
{
digitalWrite(RLED, LOW);
digitalWrite(GLED, LOW);
digitalWrite(BLED, HIGH);

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," RGB VERCLA");
  display.drawString(50,40,"MOD3");
  display.display();

}
//PURPLE (RED+BLUE)
if (mode == 4)
{
digitalWrite(RLED, 127);
digitalWrite(GLED, 0);
digitalWrite(BLED, 127);

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," RGB VERDE");
  display.drawString(50,40,"MOD4");
  display.display();

}
//TEAL (BLUE+GREEN)
else if (mode == 5)
{
digitalWrite(RLED, 0);
digitalWrite(GLED, 127);
digitalWrite(BLED, 127);

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," RGB VERME");
  display.drawString(50,40,"MOD5");
  display.display();

}
//ORANGE (GREEN+RED)
else if (mode == 6)
{
digitalWrite(RLED, 127);
digitalWrite(GLED, 127);
digitalWrite(BLED, 0);

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," RGB AZUL");
  display.drawString(50,40,"MOD6");
  display.display();

}
//WHITE (GREEN+RED+BLUE)
else if (mode == 7)
{
digitalWrite(RLED, 85);
digitalWrite(GLED, 85);
digitalWrite(BLED, 85);

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," RGB OFF");
  display.drawString(50,40,"MOD7");
  display.display();

}
//OFF (mode = 0)
else
{
digitalWrite(RLED, LOW);
digitalWrite(GLED, LOW);
digitalWrite(BLED, LOW);

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," RGB BRANCO");
  display.drawString(50,40,"MOD0");
  display.display();

}
}


void loop()
{
currentButton = debounce(lastButton); //read deboucned state
if (lastButton == LOW && currentButton == HIGH) //if it was pressed...
{
ledMode++; //increment the LED value
}
lastButton = currentButton; //reset button value
//if you've cycled through the different options,
//reset the counter to 0
if (ledMode == 8) ledMode = 0;
setMode(ledMode); //change the LED state
}
