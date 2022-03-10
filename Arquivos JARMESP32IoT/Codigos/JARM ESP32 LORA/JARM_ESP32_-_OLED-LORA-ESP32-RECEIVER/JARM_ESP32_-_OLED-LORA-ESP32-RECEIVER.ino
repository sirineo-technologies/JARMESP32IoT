/* https://robotzero.one/heltec-wifi-lora-32/
* Sketch uses 146842 bytes (14%) of program storage space. Maximum is 1044464 bytes.
* Global variables use 11628 bytes (3%) of dynamic memory, leaving 283284 bytes for local variables. Maximum is 294912 bytes.
* https://www.hackster.io/rayburne/lora-and-the-esp32-6ce9ba
*/

#include <SPI.h>
#include <LoRa.h>
#include "SSD1306.h" 


String receivedText;
String receivedRssi;
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

// the OLED used
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);
SSD1306 display(0x3c, 21, 22);


void setup() {
 
 Serial.begin(115200);
 
// while (!Serial); //if just the the basic function, must connect to a computer
 
 
 display.init();
 display.flipScreenVertically();
 display.setFont(ArialMT_Plain_16);
 display.setTextAlignment(TEXT_ALIGN_LEFT);
 display.drawString(25, 5, "SiriNEO");
 display.drawString(10, 25, "LoRa Gateway");
 display.display();
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


void loop() {
 // try to parse packet
 int packetSize = LoRa.parsePacket();
 
 if (packetSize) {
   Serial.print("Received packet '");
   display.display();
   while (LoRa.available()) {
     receivedText = (char)LoRa.read();
     Serial.print(receivedText);
     //receivedText.toCharArray(currentid, 64);
     //String pac;
     //pac = currentid;
     //Serial.print(currentid);
      //String di;
      //di = receivedText[0];
      //Serial.println(di);
 /*
     for(int i=0; i<5;i++){
      display.drawString(10, 20,String(receivedText[i]));
      String di;
      di = receivedText[0];
      Serial.print(di);
     } */
    
    
    // display.drawString(30, 20,  pac);
     //display.display();
     display.clear();
   }
   display.drawString(25, 5, "Valor LDR");
   receivedText.toCharArray(pacote, 1000);
   display.drawString(62, 30,receivedText);
   display.display();
   // print RSSI of packet
   Serial.print("' with RSSI ");
   Serial.println(LoRa.packetRssi());
  // display.drawString(0, 5, "PacketRS");
   receivedRssi = LoRa.packetRssi();
   char currentrs[64];
   receivedRssi.toCharArray(currentrs, 64);
 //  display.drawString(60, 5, currentrs);
  // display.display();
 }
 
} // ------------------------- fim loop -------------------




