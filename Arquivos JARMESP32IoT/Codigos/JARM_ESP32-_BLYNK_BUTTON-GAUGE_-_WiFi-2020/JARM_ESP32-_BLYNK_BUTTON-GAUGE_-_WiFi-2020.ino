/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  Note: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */

/*
 * SIRINEO TECHNOLOGIES
 * www.sirineo.com
 * https://www.instagram.com/sirineotechnologies/
 * Cirineu Carvalho Fernandes - SETEMBRO/2020 
 */

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "1B-zFv1bNFxcE4e-8RFoGfO4G5YZJ6ru";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "VIVO-ABA9";
char pass[] = "2F8A7AABA9";

const int analogPin = 32;  // Analog input pin 0 (GPIO 32) LDR sensor JARM ESP32 IOT
int analog_value = 0;
int timerjarm = 100;

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  
}

void loop()
{
  Blynk.run();
  AnalogPinRead();
  delay(timerjarm);
}

void AnalogPinRead() {
  analog_value = analogRead(analogPin);  // Read the analog in value:
  Serial.print("sensor = ");  // Print the results...
  Serial.println(analog_value);  // ...to the serial monitor:
  Blynk.virtualWrite(V0, analog_value);  // Send the results to Gauge Widget
  Blynk.virtualWrite(V1, analog_value);  // Send the results to Gauge Widget
} 


