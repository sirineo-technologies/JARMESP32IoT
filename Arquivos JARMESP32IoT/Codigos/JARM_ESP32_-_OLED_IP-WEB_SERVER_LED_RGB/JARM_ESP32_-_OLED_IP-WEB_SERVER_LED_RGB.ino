/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
*/

/// inicio display
#include <Wire.h>
#include "SSD1306.h" 
// Include the UI lib
#include "OLEDDisplayUi.h"

SSD1306  display(0x3c, 21, 22);




#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "engebot2";
const char* password = "abcdefgh";

WiFiServer server(80);

//const int led1 =  5;      // the number of the LED pin
//const int led2 =  26;      // the number of the LED pin
//const int led3 =  12;      // the number of the LED pin

//teste led rgb
const int led1 =  16;      // the number of the LED pin
const int led2 =  17;      // the number of the LED pin
//const int led3 =  27;      // the number of the LED pin
const int led3 =  4;      // the number of the LED pin

// Client variables 
char linebuf[80];
int charcount=0;

void setup() {
  display.init();
  // initialize the LEDs pins as an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while(!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  // attempt to connect to Wifi network:
  while(WiFi.status() != WL_CONNECTED) {
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    delay(500);
    Serial.print(".");
   }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());



//  String ipadress;
//  ipadress = (WiFi.localIP()); 
  display.flipScreenVertically();  
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,4,"JARM ESP32 IOT");
  display.drawString(27,25,"IP adress:");
 // display.drawString(5,60, String(ssid)); // imprime nome da rede
  display.drawString(13,45, WiFi.localIP().toString()); // converte e imprime o ip no display
  display.display();

  //Serial.println("IP display: ");
  //Serial.println(ipadress);
  
  
  server.begin();
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    memset(linebuf,0,sizeof(linebuf));
    charcount=0;
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        //read char by char HTTP request
        linebuf[charcount]=c;
        if (charcount<sizeof(linebuf)-1) charcount++;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML><html><head>");
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><br></head>");
          client.println("<h1>ENGEBOT TECHNOLOGY JARM ESP32 - Web Server</h1>");   
        //  client.println("<img src="http://imagizer.imageshack.us/a/img922/6015/rWMhQF.png"/>");
          client.println("<p>LED RGB RED  <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
          client.println("<p>LED RGB BLUE <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
          client.println("<p>LED RGB GREEN <a href=\"on3\"><button>ON</button></a>&nbsp;<a href=\"off3\"><button>OFF</button></a></p>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          if (strstr(linebuf,"GET /on1") > 0){
            Serial.println("LED 1 ON");
            digitalWrite(led1, LOW);
          }
          else if (strstr(linebuf,"GET /off1") > 0){
            Serial.println("LED 1 OFF");
            digitalWrite(led1, HIGH);
          }
          else if (strstr(linebuf,"GET /on2") > 0){
            Serial.println("LED 2 ON");
            digitalWrite(led2, LOW);
          }
          else if (strstr(linebuf,"GET /off2") > 0){
            Serial.println("LED 2 OFF");
            digitalWrite(led2, HIGH);
          }

           else if (strstr(linebuf,"GET /on3") > 0){
            Serial.println("LED 3 ON");
            digitalWrite(led3, LOW);
          }
          else if (strstr(linebuf,"GET /off3") > 0){
            Serial.println("LED 3 OFF");
            digitalWrite(led3, HIGH);
          }
          // you're starting a new line
          currentLineIsBlank = true;
          memset(linebuf,0,sizeof(linebuf));
          charcount=0;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

