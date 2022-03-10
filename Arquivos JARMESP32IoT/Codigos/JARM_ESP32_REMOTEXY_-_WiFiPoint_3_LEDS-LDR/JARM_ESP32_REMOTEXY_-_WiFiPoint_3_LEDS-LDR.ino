/*
  RemoteXY example. 
  Smartphone connect over Wi-Fi access point from ESP32 

  This shows an example of using the library RemoteXY.
  In the example you can control an LED e.g. on ESP_IO32 using the button on the 
  smartphone.
  
  Download the mobile app from the 
  website: http://remotexy.com/download/ for connect this sketch.
  
  Use the website http://remotexy.com/ to create your own management 
  interface your arduino with your smartphone or tablet.
  You can create different management interfaces. Use buttons, 
  switches, sliders, joysticks (g-sensor) all colors and sizes 
  in its interface. Next, you will be able to get the sample 
  code for arduino to use your interface for control from a 
  smartphone or tablet. You will not need to re-install the 
  android app, as it will determine which interface you have 
  downloaded the arduino.
  
*/

///////////////////////////////////////////// 
//        RemoteXY include library         // 
///////////////////////////////////////////// 

/* RemoteXY select connection mode and include library */ 
//#define REMOTEXY_MODE__ESP32WIFI_LIB_POINT
#define REMOTEXY_MODE__ESP32CORE_WIFI_POINT
#include <WiFi.h>
#include <RemoteXY.h> 

// RemoteXY connection settings 
\
#define REMOTEXY_WIFI_SSID "RemoteXY-jarm32"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 80


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
 { 255,3,0,4,0,101,0,8,24,1,
  2,1,21,17,22,11,36,26,31,31,
  79,78,0,79,70,70,0,2,1,21,
  30,22,11,204,26,31,31,79,78,0,
  79,70,70,0,2,1,21,43,22,11,
  121,26,31,31,79,78,0,79,70,70,
  0,129,0,12,7,37,6,106,74,65,
  82,77,32,69,83,80,51,50,0,68,
  17,1,62,61,37,8,36,129,0,16,
  56,32,4,106,76,68,82,32,74,65,
  82,77,69,83,80,51,50,0 };
  
// this structure defines all the variables of your control interface 
struct {

    // input variable
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t switch_2; // =1 if switch ON and =0 if OFF 
  uint8_t switch_3; // =1 if switch ON and =0 if OFF 

   
 // output variable
  float onlineGraph_1;

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_1 16
#define PIN_SWITCH_2 17
#define PIN_SWITCH_3 27

int pinoPOT = 32;
int brilho;
 
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_SWITCH_1, OUTPUT);
  pinMode (PIN_SWITCH_2, OUTPUT);
  pinMode (PIN_SWITCH_3, OUTPUT);
  
  // TODO you setup code

  pinMode(pinoPOT, INPUT);
  ledcSetup(ledChannel, freq, resolution);
  //ledcAttachPin(pinoLED, ledChannel);
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?HIGH:LOW);
  digitalWrite(PIN_SWITCH_2, (RemoteXY.switch_2==0)?HIGH:LOW);
  digitalWrite(PIN_SWITCH_3, (RemoteXY.switch_3==0)?HIGH:LOW);

  
  brilho = analogRead(pinoPOT);
  brilho = map(brilho, 0, 1023, 0, 255);
  ledcWrite(ledChannel, brilho);
  
  
  //int POT2 = analogRead(A0);//BEESP
  //int sensorValue = analogRead(A4); //tshield
  //int numpot2 = map(POT2, 0, 1023, 0, 100);
  //RemoteXY.level_2_pot2 = numpot2;
  //RemoteXY.onlineGraph_1_var2 = float (analogRead(A0)) / 204.8;
  
  RemoteXY.onlineGraph_1 = float (brilho);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer


}
