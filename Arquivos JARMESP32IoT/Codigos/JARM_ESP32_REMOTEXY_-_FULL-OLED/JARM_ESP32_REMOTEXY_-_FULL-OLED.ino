/*
  JARM ESP32 RemoteXY FULL

  by engereggae
  
  www.engebot.com
  www.sirineo.com
  https://twitter.com/siri_neo
  sirineotechnologies.adm@gmail.com
  
  
  RemoteXY example. 
  Smartphone connect over Wi-Fi access point from ESP32 

  This shows an example of using the library RemoteXY.
  In this example you will be able to control and interact with multiple JARM ESP32 IoT functionalities
  
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
#define REMOTEXY_MODE__ESP32WIFI_LIB_POINT
#include <WiFi.h>
#include <RemoteXY.h> 

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "RemoteXY-jarm32FULL"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 80


// LSM SENSOR

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>

//BMP 180

#include <Wire.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;


// RemoteXY configurate  
#pragma pack(push, 1)
 uint8_t RemoteXY_CONF[] =
  { 255,4,0,73,0,81,2,8,24,5,
  130,1,0,62,63,42,3,12,130,1,
  0,62,63,39,2,2,130,1,0,62,
  63,38,1,2,130,1,0,20,63,8,
  0,78,130,1,0,28,63,8,0,136,
  130,1,0,36,63,19,0,17,2,1,
  4,11,15,7,0,36,26,31,31,79,
  78,0,79,70,70,0,2,1,24,11,
  15,7,0,204,26,31,31,79,78,0,
  79,70,70,0,2,1,44,11,14,7,
  0,121,26,31,31,79,78,0,79,70,
  70,0,129,0,7,2,49,6,0,106,
  74,65,82,77,32,69,83,80,51,50,
  32,73,79,84,0,68,17,1,66,61,
  33,1,8,36,129,0,18,63,26,3,
  1,8,76,68,82,32,74,65,82,77,
  32,69,83,80,51,50,0,4,128,1,
  21,50,5,0,107,26,65,4,15,29,
  6,6,0,66,130,7,41,17,13,0,
  37,26,66,130,39,41,17,13,0,147,
  26,129,0,8,37,14,3,0,36,84,
  69,77,80,32,194,186,32,67,0,129,
  0,43,37,8,3,0,133,72,85,77,
  73,32,37,0,129,0,27,30,24,4,
  0,32,80,85,83,72,32,66,85,84,
  84,79,78,0,131,1,1,56,13,5,
  1,2,31,80,97,103,101,32,49,0,
  131,0,25,56,13,5,2,2,6,80,
  97,103,101,32,50,0,129,0,16,63,
  33,4,2,6,76,83,77,57,68,83,
  48,32,45,32,71,32,65,32,77,0,
  66,33,2,71,5,19,2,36,26,66,
  33,8,71,5,19,2,36,26,66,33,
  14,71,5,19,2,36,26,66,33,23,
  71,5,19,2,121,26,66,33,29,71,
  5,19,2,121,26,66,33,35,71,5,
  19,2,121,26,66,33,44,71,5,19,
  2,204,26,66,33,50,71,5,19,2,
  204,26,66,33,56,71,5,19,2,204,
  26,129,0,6,91,8,11,2,36,71,
  0,129,0,27,91,9,11,2,121,65,
  0,129,0,48,91,9,11,2,204,77,
  0,131,0,48,56,13,5,3,12,31,
  80,97,103,101,32,51,0,66,132,6,
  67,26,20,3,165,24,66,1,40,65,
  7,29,3,95,26,129,0,10,94,18,
  3,3,164,80,114,101,115,115,195,163,
  111,32,97,116,109,0,129,0,36,95,
  15,3,3,95,65,108,116,105,116,117,
  100,101,32,109,0,67,5,50,22,10,
  4,0,2,26,11,67,5,11,47,9,
  4,0,2,26,11,67,5,43,47,9,
  4,0,2,26,11,129,0,27,42,10,
  3,0,60,68,72,84,49,49,0,129,
  0,28,67,7,3,2,6,109,47,115,
  50,0,129,0,6,67,8,3,2,6,
  103,114,97,117,115,0,129,0,49,67,
  7,3,2,6,103,97,117,115,115,0,
  67,5,14,89,10,4,3,21,26,11,
  67,5,49,76,10,4,3,95,26,11 };
  
// this structure defines all the variables of your control interface 
struct {

   // input variable
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t switch_2; // =1 if switch ON and =0 if OFF 
  uint8_t switch_3; // =1 if switch ON and =0 if OFF 
  int8_t pwmslider; // =0..100 slider position 

    // output variable
  float onlineGraph_1;
   uint8_t led_1_button_r;// =0..255 LED Red brightness 
  int8_t tempdht11; // =0..100 level position 
  int8_t humidht11; // =0..100 level position 
  int8_t gX; // =-100..100 level position 
  int8_t gY; // =-100..100 level position 
  int8_t gZ; // =-100..100 level position 
  int8_t aX; // =-100..100 level position 
  int8_t aY; // =-100..100 level position 
  int8_t aZ; // =-100..100 level position 
  int8_t mX; // =-100..100 level position 
  int8_t mY; // =-100..100 level position 
  int8_t mZ; // =-100..100 level position 
  int8_t pressao; // =0..100 level position 
  int8_t altitudeB; // =0..100 level position

  char pwm_value[11];  // string UTF8 end zero 
  char tempV[11];  // string UTF8 end zero 
  char humV[11];  // string UTF8 end zero
  char pressao_value[11];  // string UTF8 end zero 
  char altitude_value[11];  // string UTF8 end zero  


} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_1 16
#define PIN_SWITCH_2 17
#define PIN_SWITCH_3 27

// ldr declarações

int pinoPOT = 32;
int brilho;
const int freq1 = 5000;
const int ledChanne11 = 0;
const int resolution1 = 10;

//pwm slider led

const int ledPin = 2;  //  corresponds to GPIO2
const int freq2 = 5000;
const int ledChannel2 = 1; // colocar outro canal se usar mais um pwm
const int resolution2 = 10;


// ACIONA LED REMOTEXY COM PUSH BUTTON

  // constants won't change. They're used here to
  // set pin numbers:
  const int buttonPin = 35;     // the number of the pushbutton pin
  int buttonState = 0;         // variable for reading the pushbutton status

// DHT 11 TEMP E HUMIDADE

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
//here we use 14 of ESP32 to read data
#define DHTPIN 4
//our sensor is DHT11 type
#define DHTTYPE DHT11
//create an instance of DHT sensor
DHT dht(DHTPIN, DHTTYPE);



// LSM DECLARAÇÕES

Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);  // Use I2C, ID #1000
/*
#define LSM9DS0_XM_CS 10
#define LSM9DS0_GYRO_CS 9
//Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(LSM9DS0_XM_CS, LSM9DS0_GYRO_CS, 1000);
#define LSM9DS0_SCLK 13
#define LSM9DS0_MISO 12
#define LSM9DS0_MOSI 11 
*/


// DISPLAY OLED

#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);

String tempOled;
String humiled;
String lumOled;

String pressoled;
String altOled;

void setup() // --------------------------------------setup ----------------------------------------//
{
  RemoteXY_Init (); 
  
  pinMode (PIN_SWITCH_1, OUTPUT);
  pinMode (PIN_SWITCH_2, OUTPUT);
  pinMode (PIN_SWITCH_3, OUTPUT);

  //pwm slider
 // configure LED PWM functionalitites
  ledcSetup(ledChannel2, freq2, resolution2);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel2);
  
  
  // ldr 
  pinMode(pinoPOT, INPUT);
  ledcSetup(ledChanne11, freq1, resolution1);
  //ledcAttachPin(pinoLED, ledChannel);


  // PUSH BUTTON

  pinMode(buttonPin, INPUT);

  // INICIA O DHT11

  dht.begin();


  // LSM SETUP

  #ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  Serial.begin(115200);
  Serial.println(F("LSM9DS0 9DOF Sensor Test")); Serial.println("");
  
  /* Initialise the sensor */
  if(!lsm.begin())
  {
    /* There was a problem detecting the LSM9DS0 ... check your connections */
    Serial.print(F("Ooops, no LSM9DS0 detected ... Check your wiring or I2C ADDR!"));
    while(1);
  }
  Serial.println(F("Found LSM9DS0 9DOF"));
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
  
  /* Setup the sensor gain and integration time */
  configureSensor();
  
  /* We're ready to go! */
  Serial.println("");


  bmp.begin();

  // DISPLAY OLED
  
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.fillCircle(60, 10, 10);
  display.setFont(ArialMT_Plain_16);
  display.drawString(2, 25, "      SIRINEO");
  display.drawString(0, 40, "TECHNOLOGIES");
  display.display();
  delay(2000);
  display.clear();

  // FIM LESM SETUP
  
}    // --------------------------------------fim setup ----------------------------------------//





void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?HIGH:LOW);
  digitalWrite(PIN_SWITCH_2, (RemoteXY.switch_2==0)?HIGH:LOW);
  digitalWrite(PIN_SWITCH_3, (RemoteXY.switch_3==0)?HIGH:LOW);

 
  //slider pwm---------------------

   int dutyCycle = 0;
   dutyCycle = (RemoteXY.pwmslider * 2.55);
   // changing the LED brightness with PWM
   ledcWrite(ledChannel2, dutyCycle);
  //escreve valor do pwm
   itoa (dutyCycle, RemoteXY.pwm_value, 10); 

  //FIM slider pwm---------------------

  // GRAFICO PARA LUMINOSIDADE LDR
  
  brilho = analogRead(pinoPOT);
  brilho = map(brilho, 0, 1023, 0, 255);
  ledcWrite(ledChanne11, brilho);
  RemoteXY.onlineGraph_1 = float (brilho);

  lumOled = brilho;

   // FIM GRAFICO PARA LUMINOSIDADE LDR

  // PUSH BUTTON

  // read the state of the pushbutton value:
   
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, LOW);
    RemoteXY.led_1_button_r = 255;

    //DISPLAY OLED
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0,2," JARM ESP32");
    display.drawString(0,20," PRES:");
    display.drawString(55,20,pressoled);
    display.drawString(95,20,"atm");
    display.drawString(0,35," ALT:");
    display.drawString(45,35,altOled);
    display.drawString(75,35,"m");
    display.display();

   
    
  } else {
    // turn LED off:
    digitalWrite(ledPin, HIGH);
    RemoteXY.led_1_button_r = 0;

    // DISPLAY OLED
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0,2," JARM ESP32");
    display.drawString(0,18," TEM:");
    display.drawString(44,18,tempOled);
    display.drawString(90,18,"*C");
    display.drawString(0,33," HUM:");
    display.drawString(48,33, humiled);
    display.drawString(90,33, "%");
    display.drawString(0,48," LUMI:");   
    display.drawString(48,48,lumOled); 
    display.display();
  
  }

 
  // FIM PUSH BUTTON
  
  // inicio dht11
 //use the functions which are supplied by library.
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  tempOled = t;
  humiled = h;

  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
  Serial.println("Failed to read from DHT sensor!");
   return;
   } //fim if dht11

  // VALOR TEMP E HUMIDADE GAUGES
   RemoteXY.tempdht11 = t;
   RemoteXY.humidht11 = h;

    // VALOR TEMP E HUMIDADE LABEL para escrita no labels

    itoa (t, RemoteXY.tempV, 10);
    itoa (h, RemoteXY.humV, 10);
   

  // LOOP PARA O LSM  -------------------------------------------

  /* Get a new sensor event */ 
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp); 

  // print out gyroscopic data REMOTEXY
   // observação as variáveis para aceleração e giro estão invertidas
  
   RemoteXY.gX = (accel.acceleration.x) * 10;
   RemoteXY.gY = (accel.acceleration.y) * 10;
   RemoteXY.gZ = (accel.acceleration.z) * 10;
 
   // print out accelleration data REMOTEXY

   RemoteXY.aX = (gyro.gyro.x);
   RemoteXY.aY = (gyro.gyro.y);
   RemoteXY.aZ = (gyro.gyro.z);
   
   // print out magnetometer data REMOTEXY
   
   RemoteXY.mX = (mag.magnetic.x)* 10;
   RemoteXY.mY = (mag.magnetic.y)* 10;
   RemoteXY.mZ = (mag.magnetic.z)* 10;

  // FIM LOOP PARA O LSM --------------------------------------------------


  // BMP 180


  int pres = (bmp.readPressure())/ 100;
  int pressaoatm = map(pres, 0, 2000, 0, 100);
  RemoteXY.pressao = pressaoatm;

  int alde = ((bmp.readAltitude())* (-1)) - 570; // 570 é a diferença da margem de erro em Goiania
  int altitudebm = map(alde, 0, 2000, 0, 100);
  RemoteXY.altitudeB =  altitudebm ;

  itoa (pres, RemoteXY.pressao_value, 10);
  itoa (alde, RemoteXY.altitude_value, 10);

 // lança os valores nas variavies para o display oled
 
  pressoled = pres;
  altOled = alde;

  delay(100); 

} // ------------fim void loop ------------------------------------


// FUNÇÕES PARA O LSM

void displaySensorDetails(void)
{
  sensor_t accel, mag, gyro, temp;
  lsm.getSensor(&accel, &mag, &gyro, &temp);
  // delay(500);
}


void configureSensor(void)
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);

  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  
  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  
}






