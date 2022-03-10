#include <WiFi.h>
#include "time.h"

#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);

const char* ssid       = "engebot2";
const char* password   = "abcdefgh";

const char* ntpServer = "pool.ntp.org"; //servidor de horario
//const long  gmtOffset_sec = 3600;
//const int   daylightOffset_sec = 3600;

const long  gmtOffset_sec = -4*3600;
const int   daylightOffset_sec = 3600;

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

   String txtMsg = (&timeinfo, "%A, %B %d %Y %H:%M:%S");;
   int lastStringLength = txtMsg.length();
   
   int str_len = txtMsg.length() + 1; 
   char char_array[str_len];

  char hora;
    hora = (char_array[18]+char_array[19]+char_array[20]+char_array[21]);
    
   
//   String v = lastStringLength;

   Serial.println(char_array[18]+char_array[19]+char_array[20]+char_array[21]);

   
   
  // String hora;
  // hora = (&timeinfo, "%A, %B %d %Y %H:%M:%S").toString();

  display.setFont(ArialMT_Plain_16);
//  display.setTextColor(BLACK, WHITE);
  display.drawHorizontalLine(0, 1, 127);
  display.drawHorizontalLine(0, 2, 127);
  display.drawHorizontalLine(0, 3, 127);
  display.drawString(0,5,"   HORA LOCAL");
  //display.drawString(0,10, lastStringLength.toString());
  //display.drawString(23,20,hora.toString());
  // display.drawHorizontalLine(distanciaH,distanciaV, caractere);
  display.drawHorizontalLine(0, 25, 127);
  display.drawHorizontalLine(0, 26, 127);
  display.drawHorizontalLine(0, 27, 127);
 // display.drawVerticalLine(0, 29, 30); //desenha uma linha vertical
  //display.drawVerticalLine(0, 30, 10);
 // display.drawVerticalLine(0, 31, 10);
 // display.drawRect(0, 31, 20,30); //desenha retangulo 20-> horizontal 30-> vertical
  display.drawRect(0, 31, 127,30); //desenha retangulo 20-> horizontal 30-> vertical
  display.drawRect(3, 33, 120,25); //desenha retangulo 20-> horizontal 30-> vertical
  //desenha circulo
  display.drawCircle(10, 50, 10); //desenha circulo 20-> horizontal 30-> vertical
  display.fillCircle(25, 50, 10); //desenha circulo 20-> horizontal 30-> vertical
  display.display();


  
}

void setup()
{
  
  
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "JARM ESP32 OLED Start");
  display.display();
  delay(500);
  display.clear();

  
  Serial.begin(115200);
  Serial.println("");
  Serial.print("WiFi conectado. Endereço IP: ");
  Serial.println(WiFi.localIP());
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password); // iniciar o wifi
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print("."); // imprime um ponto até conectar
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  
} // fim setup

void loop()
{
  delay(1000);
  printLocalTime();
  display.clear();

  String timereal;
//  timereal =  printLocalTime();
  
  
}





