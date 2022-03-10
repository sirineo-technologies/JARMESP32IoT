#include "DFRobot_SHT20.h"
#include <Wire.h>
#include <SPI.h>              // include libraries
#include <LoRa.h>
#include "FS.h"
#include "SD.h"
#include "SSD1306.h" 
// Include the UI lib
#include "OLEDDisplayUi.h"

const int csPin = 5;          // LoRa radio chip select
const int resetPin = 14;       // LoRa radio reset
const int irqPin = 13;

byte localAddress = 0xBB;
byte destinationAddress = 0xAA;
long lastSendTime = 0;
int interval = 2000;
int count = 0;

DFRobot_SHT20    sht20;

//#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);

String tempe;

int counter = 1;

String LoRaGet = "";
String LoRaMessage = "";
String SDMessage = "";
String receivedText;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
int LAMP = 25;
int FAN = 04; 

String strTemp = "Temperatura: ";
String strHumd = "Umidade: ";
String strLampOn = "Lampada Ligada: ";
String strFanOn = "FAN Ligada: ";
float tempMAX = 37.00;
float tempMIN = 29.00;
int countLamp = 0;
int countFan = 0;
bool lampOn = false;
bool FANOn = false;
int intlampOn = 0;
int intFANOn = 0;
String currentTime = "";
String LoRaReceived = "";

float humd;
float temp;

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void(* resetFunc) (void) = 0;//declare reset function at address 0

void registrarSD(String SDMessage){
       File dataFile = SD.open("/monitor.csv", FILE_APPEND);
     if(!dataFile){
       dataFile = SD.open("/monitor.csv",FILE_WRITE);
        if (!dataFile) {
            // It failed too, so give up.
            Serial.println("Failed to open file.txt");
        }
     }
      dataFile.println(SDMessage);
      dataFile.close();
      
      delay(900);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start LoRa duplex");
  Serial.print("Local address: ");
  Serial.println(String(localAddress, HEX));
  Serial.print("Destination address: ");
  Serial.print(String(destinationAddress, HEX));

  SPI.begin();
  
  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(915E6)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true) {}
  }

  pinMode(LAMP, OUTPUT);
  delay(10000);
  pinMode(FAN, OUTPUT);

  sht20.initSHT20();                                  // Init SHT20 Sensor
  delay(1000);
  sht20.checkSHT20();                                 // Check SHT20 Sensor


  if(!SD.begin(33)){
      Serial.println("Card Mount Failed");
      return;
   }
   
  uint8_t cardType = SD.cardType();
}

void loop() {
  if (millis() - lastSendTime > interval) {

    humd = sht20.readHumidity();                  // Read Humidity
    temp = sht20.readTemperature();               // Read Temperature

    Serial.println("TEMP MAX: "+(String)tempMAX+" TEMP MIN: "+(String)tempMIN);

    // ESCREVER OS DADOS DA  TEMP
       
        String tempiC;
        tempiC =  temp;
        String umid;
        umid =  humd;
            
        String intLAMP;
        intLAMP = intlampOn;
        String intFAN;
        intFAN = intFANOn;
        
        LoRaMessage = tempiC + "-" + umid +"-" +intFAN+ "-" +intLAMP;
        SDMessage = strTemp+"; "+tempiC+"; "+strHumd+"; "+umid+"; "+strLampOn+"; "+countLamp+"; "+strLampOn+"; "+countFan+ "; " + currentTime+"\n";

        registrarSD(SDMessage);
        
        sendMessage(LoRaMessage);
        Serial.println("Sending " + LoRaMessage);
   
        Serial.print(" from source 0x" + String(localAddress, HEX));
        Serial.println(" to destination 0x" + String(destinationAddress, HEX));

          if(LoRaReceived != ""){
           String strMax;
           String strMin;
           strMax  = getValue(LoRaReceived, ';', 0);
           strMin  = getValue(LoRaReceived, ';', 1);
           currentTime = getValue(LoRaReceived, ';', 2);
           
           tempMAX = strMax.toFloat();
           tempMIN = strMin.toFloat();

           delay(900);
           
          }
          
              if(temp>tempMAX && FANOn == false){
                      digitalWrite(FAN, HIGH);
                      countFan++;
                      FANOn = true;
                      intFANOn = 1;
                    }
                    
                    if(temp<tempMAX && FANOn == true){
                      digitalWrite(FAN, LOW);
                      FANOn = false;
                      intFANOn = 0;
                    }
                    if(temp<tempMIN && lampOn == false){
                      digitalWrite(LAMP, HIGH);
                      countLamp++;
                      lampOn = true;
                      intlampOn = 1;
                      Serial.println("TA ON");
                    }
                    if(temp>tempMIN && lampOn == true) {
                      digitalWrite(LAMP, LOW);
                      lampOn = false;
                      intlampOn = 0;
                       Serial.println("TA Off");
                    }

                    delay(900);

          if(temp == 998.00){
              resetFunc(); 
          }


          lastSendTime = millis();
          interval = random(2000) + 78000;
  }

  receiveMessage(LoRa.parsePacket());
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();
  LoRa.write(destinationAddress);
  LoRa.write(localAddress);
  LoRa.write(outgoing.length());
  LoRa.print(outgoing);
  LoRa.endPacket();

  delay(900);
}

void receiveMessage(int packetSize) {
  if (packetSize == 0) return;

  int recipient = LoRa.read();
  byte sender = LoRa.read();
  byte incomingLength = LoRa.read();

  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length()) {
    Serial.println("Error: Message length does not match length");
    return;
  }

  if (recipient != localAddress) {
    Serial.println("Error: Recipient address does not match local address");
    return;
  }
  

  LoRaReceived = incoming;
  
  Serial.print("Received data " + incoming);
  Serial.print(" from 0x" + String(sender, HEX));
  Serial.println(" to 0x" + String(recipient, HEX));

  delay(900);
}
