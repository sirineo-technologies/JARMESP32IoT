/* https://robotzero.one/heltec-wifi-lora-32/
* Sketch uses 146842 bytes (14%) of program storage space. Maximum is 1044464 bytes.
* Global variables use 11628 bytes (3%) of dynamic memory, leaving 283284 bytes for local variables. Maximum is 294912 bytes.
* https://www.hackster.io/rayburne/lora-and-the-esp32-6ce9ba
*/

#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>
#include "SSD1306.h" 
#include "ThingSpeak.h"


String receivedText;
String receivedRssi;
String LoRaMessage = "";


String SDMessage = "";



int delimiter;
char pacote[10] ;
// WIFI_LoRa_32 ports
// GPIO5  -- SX1278's SCK
// GPIO19 -- SX1278's MISO
// GPIO27 -- SX1278's MOSI
// GPIO18 -- SX1278's CS
// GPIO14 -- SX1278's RESET
// GPIO26 -- SX1278's IRQ(Interrupt Request)

#define SS 5
#define RST 14
#define DI0 13
//#define BAND 902E6 //915E6
#define BAND 915E6
#define CHANNEL_ID 1571918
#define CHANNEL_API_KEY "DDB27O1EZ4CFRH8P"
#define WIFI_TIMEOUT_MS 20000
#define WIFI_NETWORK "LOPES2.4G"
#define WIFI_PASSWORD "lopes3287"


WiFiClient client;

int counter = 0;

// the OLED used
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);
SSD1306 display(0x3c, 21, 22);

void connectToWifi(){


  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(WIFI_NETWORK);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

}
void setup() {
 
 Serial.begin(115200);
 
// while (!Serial); //if just the the basic function, must connect to a computer
 
 connectToWifi();
 ThingSpeak.begin(client);
 
 delay(2000);

 SPI.begin();
 LoRa.setPins(SS, RST, DI0);
 Serial.println("LoRaBOT Receiver");
 
 if (!LoRa.begin(BAND)) {
   Serial.println("Starting LoRa failed!");
   display.drawString(0, 1, "Starting LoRa failed!");
   while (1);
 }

  
} // ---------------------------------------------------------------fim setup



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

void loop() {
 // try to parse packet
 String splitter;
 int packetSize = LoRa.parsePacket();
 
 if (packetSize) {
   Serial.print("Received packet :");
   display.display();
   while (LoRa.available()) {
     receivedText = (char)LoRa.read();
     splitter += receivedText;

 /*
     for(int i=0; i<5;i++){
      display.drawString(10, 20,String(receivedText[i]));
      String di;
      di = receivedText[0];
      Serial.print(di);
     } */
    
    
    // display.drawString(30, 20,  pac);
     //display.display();

   }

   String tempe = getValue(splitter, '-', 0);
String humid = getValue(splitter, '-', 1);
String fan = getValue(splitter, '-', 2);
String lamp = getValue(splitter, '-', 3);

ThingSpeak.setField(1, tempe);
ThingSpeak.setField(2, humid);
ThingSpeak.setField(7, lamp);
ThingSpeak.setField(8, fan);

ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);


 
 }


} // ------------------------- fim loop -------------------





