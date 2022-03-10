int ThermistorPin = 25;
int Vo;
float R1 = 10000;
float logR2, R2, T, c, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
//#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET); 


void setup() {
Serial.begin(115200);

//display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
//display.display();
//delay(500);
//display.clearDisplay();
//display.setTextColor(WHITE);
//  display.setTextSize(2);
 // display.setCursor(0,0);
 // display.print("    JARM ");
 // display.setCursor(0,17);
 // display.print("   IOT M ");
 // display.display();
 // delay(1000); 

 // fim oled e real time setup

}

void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  c = T - 273.15;
  Tf = (c * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(c);
  Serial.println(" C");

/*
  // ESCREVER OS DADOS DA LUMINOSIDADE OU TEMP

  if (c<30){
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(5,3);
  display.setTextSize(1);
  display.print("TEMPERATURE Celsius");
  display.setCursor(22,15);
  display.setTextSize(2);
  display.print(c);
  display.print(" C"); 
  display.display();
  }
  else{
     display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(5,3);
  display.setTextSize(1);
  display.print("TEMPERATURE Fahren.");
  display.setCursor(22,15);
  display.setTextSize(2);
  display.print(Tf);
  display.print(" F"); 
  display.display();
  }
  */
    

  delay(500);
}
