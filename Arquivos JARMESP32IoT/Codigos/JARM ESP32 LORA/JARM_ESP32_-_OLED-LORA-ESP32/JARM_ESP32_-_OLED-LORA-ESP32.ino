/* https://www.alictronix.com/archives/860
* Sketch uses 155594 bytes (14%) of program storage space. Maximum is 1044464 bytes.
* Global variables use 11612 bytes (3%) of dynamic memory, leaving 283300 bytes for local variables. Maximum is 294912 bytes.
*/
#include <SPI.h>
#include <LoRa.h>
#include "SSD1306.h" 
// Include the UI lib
#include "OLEDDisplayUi.h"
#include <Arduino.h>
//OLED pins to ESP32 GPIOs via this connecthin:
//OLED_SDA — GPIO4
//OLED_SCL — GPIO15
//OLED_RST — GPIO16
SSD1306 display(0x3c, 21, 22);
// WIFI_LoRa_32 ports
// GPIO5 — SX1278’s SCK
// GPIO19 — SX1278’s MISO
// GPIO27 — SX1278’s MOSI
// GPIO18 — SX1278’s CS
// GPIO14 — SX1278’s RESET
// GPIO26 — SX1278’s IRQ(Interrupt Request)
#define SS 5
#define RST 14
#define DI0 13
#define BAND 902E6 //915E6
int counter = 0;
void setup() {
 pinMode(16, OUTPUT); //Send success, LED will bright 1 second
 pinMode(24, OUTPUT);
 //digitalWrite(16, LOW); // set GPIO16 low to reset OLED
 delay(50);
 //digitalWrite(16, HIGH);
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
}
void loop() {
 Serial.print("Sending packet: ");
 Serial.println(counter);
 display.clear();
 display.setFont(ArialMT_Plain_16);
 display.drawString(3, 5, "Sending packet ");
 display.drawString(50, 30, String(counter));
 display.display();
 // send packet
 LoRa.beginPacket() ;
 LoRa.print("Hello ") ;
 LoRa.print(counter) ;
 LoRa.endPacket();
 counter++;
 digitalWrite(2, HIGH); // turn the LED on (HIGH is the voltage level)
 delay(1000); // wait for a second
 digitalWrite(2, LOW); // turn the LED off by making the voltage LOW
 delay(1000); // wait for a second
 delay(3000);
}

