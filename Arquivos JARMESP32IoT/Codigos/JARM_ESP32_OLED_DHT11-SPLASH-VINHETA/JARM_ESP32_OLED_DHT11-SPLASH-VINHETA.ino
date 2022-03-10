// Example testing sketch for various DHT humidity/temperature sensors written by ladyada
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 4     //JARM ESP32 IOT 32  Digital pin connected to the DHT sensor


// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// DISPLAY OLED

#include "SSD1306.h" 
#include "OLEDDisplayUi.h"
SSD1306 display(0x3c, 21, 22);

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

// JINGLE
int freq = 2000;
int channel = 0;
int resolution = 8;

void setup() {
  
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  Serial.println(F("OLA JARM ESP32 IOT!"));
  dht.begin();

  
 // INIT DISPLAY
 display.init();
 display.flipScreenVertically();
 display.fillCircle(60, 9, 9);
 display.setFont(ArialMT_Plain_16);
 display.drawString(2, 23, "      SIRINEO");
 display.drawString(0, 37, "TECHNOLOGIES");
 display.display();

 // ----------- VINHETA DE INICIO -------------//
 ledcSetup(channel, freq, resolution);
 ledcAttachPin(26, channel);
 ledcWriteTone(channel, 1005);
 delay(1000);
 ledcWriteTone(channel, 1255);
 delay(1000);
 ledcWriteTone(channel, 1505);
 delay(1000); 
 // ----------- FIM VINHETA DE INICIO -------------//
 
 delay(3000);

  
}

void loop() {
  
  // ----------- CANCELA  VINHETA DE INICIO -------------//

  ledcSetup(channel, freq, resolution);
  ledcAttachPin(26, channel);
  ledcWriteTone(channel, 0);
  
  // Wait a few seconds between measurements.
 
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(3, 2, "   ** LEITURA DHT 11 **  ");
  display.drawString(1, 15, "TEMP CELSIUS: " + String(t) + " °C " );
  display.drawString(1, 30, "TEMP FAHRE. : " + String(f) + " °F" );
  display.drawString(1, 45, "HUM: " + String(h) + " % " );
  display.display();

}





