

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>

//display oled
#include "SSD1306.h" // alias for #include "SSD1306Wire.h"

//for wire
//#define I2C_SDA_PIN 21
//#define I2C_SCL_PIN 22

SSD1306  display(0x3c, 21, 22);

int contadorx;
int contadory;
int contadorz;

// JINGLE
int freq = 2000;
int channel = 0;
int resolution = 8;

// Assign a unique base ID for this sensor */   
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);  // Use I2C, ID #1000


/* Or, use Hardware SPI:
  SCK -> SPI CLK
  SDA -> SPI MOSI
  G_SDO + XM_SDO -> tied together to SPI MISO
  then select any two pins for the two CS lines:
*/

//#define LSM9DS0_XM_CS 10
//#define LSM9DS0_GYRO_CS 9

//Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(LSM9DS0_XM_CS, LSM9DS0_GYRO_CS, 1000);

/* Or, use Software SPI:
  G_SDO + XM_SDO -> tied together to the MISO pin!
  then select any pins for the SPI lines, and the two CS pins above
*/

//#define LSM9DS0_SCLK 13
//#define LSM9DS0_MISO 12
//#define LSM9DS0_MOSI 11

//Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(LSM9DS0_SCLK, LSM9DS0_MISO, LSM9DS0_MOSI, LSM9DS0_XM_CS, LSM9DS0_GYRO_CS, 1000);


/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensorDetails(void)
{
  sensor_t accel, mag, gyro, temp;
  
  lsm.getSensor(&accel, &mag, &gyro, &temp);
  
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(accel.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(accel.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(accel.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(accel.max_value); Serial.println(F(" m/s^2"));
  Serial.print  (F("Min Value:    ")); Serial.print(accel.min_value); Serial.println(F(" m/s^2"));
  Serial.print  (F("Resolution:   ")); Serial.print(accel.resolution); Serial.println(F(" m/s^2"));  
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));

  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(mag.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(mag.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(mag.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(mag.max_value); Serial.println(F(" uT"));
  Serial.print  (F("Min Value:    ")); Serial.print(mag.min_value); Serial.println(F(" uT"));
  Serial.print  (F("Resolution:   ")); Serial.print(mag.resolution); Serial.println(F(" uT"));  
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));

  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(gyro.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(gyro.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(gyro.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(gyro.max_value); Serial.println(F(" rad/s"));
  Serial.print  (F("Min Value:    ")); Serial.print(gyro.min_value); Serial.println(F(" rad/s"));
  Serial.print  (F("Resolution:   ")); Serial.print(gyro.resolution); Serial.println(F(" rad/s"));  
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));

  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(temp.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(temp.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(temp.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(temp.max_value); Serial.println(F(" C"));
  Serial.print  (F("Min Value:    ")); Serial.print(temp.min_value); Serial.println(F(" C"));
  Serial.print  (F("Resolution:   ")); Serial.print(temp.resolution); Serial.println(F(" C"));  
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
  
  delay(500);
}

/**************************************************************************/
/*
    Configures the gain and integration time for the TSL2561
*/
/**************************************************************************/
void configureSensor(void)
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void) 
{

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

//  Wire.begin( I2C_SDA_PIN, I2C_SCL_PIN );
 // Wire.begin();

  //inicia dlispay
  display.init();
  
  Serial.begin(115200);
  Serial.println(F("LSM9DS0 9DOF Sensor Test")); Serial.println("");
  
  /* Initialise the sensor */

  lsm.begin();
  /*
  if(!lsm.begin())
  {
     There was a problem detecting the LSM9DS0 ... check your connections 
    Serial.print(F("Ooops, no LSM9DS0 detected ... Check your wiring or I2C ADDR!"));
    while(1);
  }

  */
  Serial.println(F("Found LSM9DS0 9DOF"));
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
  /* Setup the sensor gain and integration time */
  configureSensor();
  /* We're ready to go! */
  Serial.println("");
}


void loop(void) 
{  
  
 // ----------- CANCELA  VINHETA DE INICIO -------------//

 // ledcSetup(channel, freq, resolution);
 // ledcAttachPin(26, channel);
 // ledcWriteTone(channel, 0);
  
 // ----------- FIM CANCELA  VINHETA DE INICIO -------------//  
  
  
  /* Get a new sensor event */ 
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp); 
  Serial.println("SiriNEO Technoogies - LSM 9S0 dados:");
  
  // print out accelleration data
  //obseravção: esses dados são giroscopio
 // Serial.print("Gyro  X: "); Serial.print(gyro.gyro.x); Serial.print(" ");
 // Serial.print("Accel X: "); Serial.print(accel.acceleration.x); Serial.print(" ");
  Serial.print("Gyro X: "); Serial.print((accel.acceleration.x)*10); Serial.print(char(176));  Serial.print(" ");
  Serial.print("  \tY: "); Serial.print((accel.acceleration.y)*10); Serial.print(char(176)); Serial.print(" ");
  Serial.print("  \tZ: "); Serial.print((accel.acceleration.z)*10); Serial.print(char(176));  Serial.println("  \tmdps");

  
  int valorx;
  valorx = (accel.acceleration.x)*10;
  Serial.print("Vx>> ");
 // Serial.println(valorx);
  contadorx = valorx;
 // display.clear();
  //desenha a progress bar
  drawProgressBarx();
 // display.display();


  int valory;
  valory = (accel.acceleration.y)*10;
  Serial.print("Vy>> ");
 // Serial.println(valory);
  contadory = valory;
  drawProgressBary();
 
   
  int valorz;
  valorz = (accel.acceleration.z)*10;
  Serial.print("Vz>> ");
 //
 Serial.println(valorz);
  contadorz = valorz;
  //desenha a progress bar
  drawProgressBarz();
  
  display.display();
  display.clear();

  // print out magnetometer data
  Serial.print("Magn. X: "); Serial.print(mag.magnetic.x);  Serial.print(" ");
  Serial.print("  \tY: "); Serial.print(mag.magnetic.y);       Serial.print(" ");
  Serial.print("  \tZ: "); Serial.print(mag.magnetic.z);     Serial.println("  \tgauss");
  
  // print out gyroscopic data
  //obseravção: esses dados são acelerometro
  //Serial.print("Gyro  X: "); Serial.print(gyro.gyro.x); Serial.print(" ");
  Serial.print("Accel  X: "); Serial.print(gyro.gyro.x); Serial.print(" ");
  Serial.print("  \tY: "); Serial.print(gyro.gyro.y);       Serial.print(" ");
  Serial.print("  \tZ: "); Serial.print(gyro.gyro.z);     Serial.println("  \tm/s^2");

  // print out temperature data
  //Serial.println("\n");
  Serial.print("Temp: "); Serial.print(temp.temperature); 
  Serial.print(char(176));
  Serial.println(" C");
  Serial.println("**********************\n");

  delay(100);
}

// INICIO BARRA x

void drawProgressBarx() {
  
  display.flipScreenVertically(); 
  display.drawProgressBar(25, 5, 100, 10, contadorx);
  //Serial.print("x>> ");
  Serial.println(contadorx);
  //Serial.println(valor);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(10, 1, "x :");
   
}

// INICIO BARRA y

void drawProgressBary() {
  
  display.flipScreenVertically(); 
  display.drawProgressBar(25, 29, 100, 10, contadory);
  //Serial.print("y>> ");
  Serial.println(contadory);
  //Serial.println(valor);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(10, 25, "y :");
   
}


// INICIO BARRA z

void drawProgressBarz() {
  
  display.flipScreenVertically(); 
  display.drawProgressBar(25, 52, 100, 10, contadorz);
  //Serial.print("z>> ");
  Serial.println(contadorz);
  //Serial.println(valor);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(10, 47, "z :");
   
}





