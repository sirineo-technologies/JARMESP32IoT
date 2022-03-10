#include "DFRobot_SHT20.h"

#include <Wire.h>
#include "SSD1306.h" 
// Include the UI lib
#include "OLEDDisplayUi.h"
#include <SPI.h>
#include <LoRa.h>
#include <Time.h>
#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"


#define SS 5
#define RST 14
#define DI0 13
//#define BAND 902E6 //915E6
#define BAND 915E6


SSD1306  display(0x3c, 21, 22);
//SSD1306  display(0x78, 21, 22);

DFRobot_SHT20    sht20;

//#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);

String tempe;

int counter = 1;

String LoRaMessage = "";
String SDMessage = "";
String receivedText;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

// -----------------declaração pinos acionamento lampada e ventilador ------------------
int LAMP = 35;
int FAN = 04; 
// ----------------- fim acionamento lampada e ventilador ------------------

float tempMAX = 28;
float tempMIN = 25.9;
int countLamp = 0;
int countFan = 0;
bool lampOn = false;
bool FANOn = false;
int intlampOn = 0;
int intFANOn = 0;


//ldr
int pinoPOT = 32;
int brilho;




void setup()
{

 pinMode(LAMP, OUTPUT);
 pinMode(FAN, OUTPUT);
  display.init();
  display.flipScreenVertically();
 
//ldr
 pinMode(pinoPOT, INPUT);
 ledcSetup(ledChannel, freq, resolution);
 
  
 pinMode(17, OUTPUT); //Send success, LED will bright 1 second
 pinMode(24, OUTPUT);
 
 digitalWrite(17, LOW); // set GPIO16 low to reset OLED
 delay(1000);
 digitalWrite(17, HIGH);

 
 Serial.begin(115200);
 while (!Serial); //If just the the basic function, must connect to a computer
 // Initialising the UI will init the display too.
 display.init();
 display.flipScreenVertically();
 display.setFont(ArialMT_Plain_10);
 display.setTextAlignment(TEXT_ALIGN_LEFT);
 display.drawString(5, 5, "LoRa Sender");
 display.display();
 
 SPI.begin();
 LoRa.setPins(SS, RST, DI0);
 Serial.println("LoRa Sender");
 if (!LoRa.begin(BAND)) {
   Serial.println("Starting LoRa failed!");
   while (1);
 }
 Serial.println("LoRa Initial OK!");
 display.drawString(5, 20, "LoRa Initializing OK!");
 display.display();
  delay(2000);
    
   sht20.initSHT20();                                  // Init SHT20 Sensor
   // delay(100);
   sht20.checkSHT20();                                 // Check SHT20 Sensor
   
     if(!SD.begin(33)){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();



}


void loop()
{
    
    float humd = sht20.readHumidity();                  // Read Humidity
    float temp = sht20.readTemperature();               // Read Temperature


    // ESCREVER OS DADOS DA  TEMP
 

  String tempiC;
  tempiC =  temp;
  String umid;
  umid =  humd;

if(temp>tempMAX && FANOn == false){
  digitalWrite(FAN, HIGH);
  countFan++;
  FANOn = true;
  intFANOn = 1;
}

if(temp<tempMAX){
  digitalWrite(FAN, LOW);
  FANOn = false;
  intFANOn = 0;
}
if(temp<tempMIN && lampOn == false){
  digitalWrite(LAMP, HIGH);
  countLamp++;
  lampOn = true;
  intlampOn = 1;
}
if(temp>tempMIN) {
  digitalWrite(LAMP, LOW);
  lampOn = false;
  intlampOn = 0;
}

String intLAMP;
intLAMP = intlampOn;
String intFAN;
intFAN = intFANOn;

  
 brilho = analogRead(pinoPOT);
 
 LoRaMessage = tempiC + "-" + umid +"-" +intFAN+ "-" +intLAMP;
 SDMessage = "Temperatura: "+tempiC+"; "+"Umidade: "+umid+"; "+"Lampada Ligada: "+countLamp+"; "+"FAN Ligada: "+countFan+"\n";
 
 //File dataFile = SD.open("/monitor.txt", FILE_APPEND);
 File dataFile = SD.open("/monitor.csv", FILE_APPEND);
 if(!dataFile){
   dataFile = SD.open("/monitor.txt",FILE_WRITE);
    if (!dataFile) {
        // It failed too, so give up.
        Serial.println("Failed to open file.txt");
    }
 }
  dataFile.println(SDMessage);
  dataFile.close();




  
 //LoRaMessage = String(counter);
 Serial.println("This is the message:" + LoRaMessage);
 LoRa.beginPacket() ;
 LoRa.print(LoRaMessage) ;
 LoRa.endPacket();
 counter++;




  digitalWrite(2, HIGH); // turn the LED on (HIGH is the voltage level)
 delay(1000); // wait for a second
 digitalWrite(2, LOW); // turn the LED off by making the voltage LOW
 delay(1000); // wait for a second
    
    
   delay(30000);
}
