
//int delayt = 0;

  // ligado ao led azul wroombee
int ledPin;
const int BUTTON=35; //The Button is connected to pin 2
boolean lastButton = LOW; //Last Button State
boolean currentButton = LOW; //Current Button State
int ledMode = 0; //Cycle between LED states

int currentresult;

#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
  pinMode (BUTTON, INPUT); //Set button as input (not required)
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

 //int currentresult;
currentButton = debounce(lastButton); //read deboucned state
if (lastButton == LOW && currentButton == HIGH) //if it was pressed...
{
ledMode++; //increment the LED value
}
lastButton = currentButton; //reset button value
//if you've cycled through the different options,
//reset the counter to 0
if (ledMode == 4) ledMode = 0;
setMode(ledMode); //change the LED state

                         
}

int mysoma(int m, int n){
  int result;
  result = m + n;
  return result;
  
}

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


void setMode(int mode)
{
//RED
if (mode == 1)
{
  ledPin = 17;
  for (int i = 0; i < 1000; i++){
  currentresult = mysoma(i,i+1);
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(currentresult);                       // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(currentresult); 
  //Serial.println(currentresult);  
  String led = String(ledPin);
  Serial.println(led);  
  
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," BLYNK TIME");
  String voled = String(currentresult);
  display.drawString(40,40,voled + " s");
  display.display();
  
  }

}
//GREEN
 if (mode == 2)
{

  ledPin = 16;
  for (int i = 0; i < 1000; i++){
  currentresult = mysoma(i,i+1);
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(currentresult);                       // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(currentresult); 
  //Serial.println(currentresult);  
  String led = String(ledPin);
  Serial.println(led);  
  
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," BLYNK TIME");
  String voled = String(currentresult);
  display.drawString(40,40,voled + " s");
  display.display();
  
  }

}

//GREEN
 if (mode == 3)
{

 ledPin = 27;
 for (int i = 0; i < 1000; i++){
  currentresult = mysoma(i,i+1);
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(currentresult);                       // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(currentresult); 
  //Serial.println(currentresult);  
  String led = String(ledPin);
  Serial.println(led);  
  
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,2," JARM ESP32");
  display.drawString(10,23," BLYNK TIME");
  String voled = String(currentresult);
  display.drawString(40,40,voled + " s");
  display.display();
  
  }

}

} // fim







