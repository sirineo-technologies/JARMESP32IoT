#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
#define NUMFLAKES 5
#define XPOS 0
#define YPOS 1
#define DELTAY 2
 
//Notas musicais
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
 
//tempo
#define WHOLE 500
#define HALF 250
#define QUARTER 125
#define EIGHTH 62.5
#define SIXTEENTH 31.25
 
#define CHANELL    0
#define FREQUENCE  2000
#define RESOLUTION 10
#define BUZZER_PIN GPIO_NUM_26                                                   
 
static const unsigned char PROGMEM snowFlake[] =
{
B00000100 , B00100000 ,
B00000010 , B01000000 ,
B00101001 , B10010100 ,
B00011001 , B10011000 ,
B00111001 , B10011100 ,
B10000101 , B10000101 ,
B01000011 , B11000010 ,
B00111110 , B01111100 ,
B00111110 , B01111100 ,
B01000011 , B11000010 ,
B10000101 , B10000101 ,
B00111001 , B10011100 ,
B00011001 , B10011000 ,
B00101001 , B10010100 ,
B00000010 , B01000000 ,
B00000100 , B00100000 
};
 
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
 
void jingleBell(void *pvParameters){
 for (byte i=0;i<2;i++){ 
  ledcWriteTone(CHANELL,NOTE_C4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_C4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_G4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_F4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_C4);
  delay(WHOLE+HALF);
 
  ledcWriteTone(CHANELL,NOTE_C4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_C4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_G4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_F4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_D4);
  delay(WHOLE+HALF);
 
  ledcWriteTone(CHANELL,NOTE_D4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_D4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_AS4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_G4);
  delay(HALF);
  if (i == 0){
    ledcWriteTone(CHANELL,NOTE_E4);
    delay(WHOLE+HALF);
  }
  else{
    ledcWriteTone(CHANELL,NOTE_C5);
    delay(WHOLE+HALF);
  }
 
  if (i == 0){
    ledcWriteTone(CHANELL,NOTE_C5);
    delay(HALF);
    ledcWriteTone(CHANELL,NOTE_D5);
    delay(HALF);
    ledcWriteTone(CHANELL,NOTE_C5);
    delay(HALF);
    ledcWriteTone(CHANELL,NOTE_G4);
    delay(HALF);
    ledcWriteTone(CHANELL,NOTE_GS4);
    delay(HALF);
    ledcWriteTone(CHANELL,NOTE_A4);
    delay(WHOLE+HALF);
  }
 
  else{
    
    ledcWriteTone(CHANELL,NOTE_C5);
    delay(HALF);
    ledcWriteTone(CHANELL,NOTE_D5);
    delay(HALF);
    ledcWriteTone(CHANELL,NOTE_C5);
    delay(HALF);
    ledcWriteTone(CHANELL,NOTE_AS4);
    delay(HALF);
    ledcWriteTone(CHANELL,NOTE_G4);
    delay(HALF);
    ledcWriteTone(CHANELL,NOTE_F4);
    delay(WHOLE+HALF);
  }
 
  delay(100);
 }
  ledcWriteTone(CHANELL, 0);
  delay(125);
 
  for (byte i = 0; i<2;i++){
    ledcWriteTone(CHANELL,NOTE_A4);
    delay(HALF);
    ledcWriteTone(CHANELL, 0);
    ledcWriteTone(CHANELL,NOTE_A4);
    delay(HALF);
    ledcWriteTone(CHANELL, 0);
    ledcWriteTone(CHANELL,NOTE_A4);
    delay(HALF);
    ledcWriteTone(CHANELL, 0);
    ledcWriteTone(CHANELL,NOTE_A4);
    delay(HALF);
    ledcWriteTone(CHANELL, 0);
    delay(25);
  }
 
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_C5);
  delay(HALF);    
  ledcWriteTone(CHANELL,NOTE_F4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_G4);
  delay(HALF);    
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(HALF+WHOLE);
  ledcWriteTone(CHANELL, 0);
  
  delay(25);
  ledcWriteTone(CHANELL, 0);
  ledcWriteTone(CHANELL,NOTE_AS4);
  delay(HALF);
  ledcWriteTone(CHANELL, 0);
  ledcWriteTone(CHANELL,NOTE_AS4);
  delay(HALF);    
  ledcWriteTone(CHANELL, 0);
  ledcWriteTone(CHANELL,NOTE_AS4);
  delay(WHOLE);
  delay(25);
  ledcWriteTone(CHANELL, 0);
  ledcWriteTone(CHANELL,NOTE_AS4);
  delay(HALF);  
  ledcWriteTone(CHANELL, 0);  
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(HALF);
  ledcWriteTone(CHANELL, 0);
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(WHOLE);
  ledcWriteTone(CHANELL, 0);
  
  ledcWriteTone(CHANELL,NOTE_G4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_G4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_G4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_C5);
  delay(HALF+WHOLE);
  ledcWriteTone(CHANELL, 0);
  delay(25);
 
  for (byte i = 0; i<2;i++){
    ledcWriteTone(CHANELL,NOTE_A4);
    delay(HALF);
    ledcWriteTone(CHANELL, 0);
    ledcWriteTone(CHANELL,NOTE_A4);
    delay(HALF);
    ledcWriteTone(CHANELL, 0);
    ledcWriteTone(CHANELL,NOTE_A4);
    delay(HALF);
    ledcWriteTone(CHANELL, 0);
    ledcWriteTone(CHANELL,NOTE_A4);
    delay(HALF);
    ledcWriteTone(CHANELL, 0);
    delay(25);
  }
 
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_C5);
  delay(HALF);    
  ledcWriteTone(CHANELL,NOTE_F4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_G4);
  delay(HALF);    
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(WHOLE+WHOLE);
  ledcWriteTone(CHANELL, 0);
 
  delay(25);
  ledcWriteTone(CHANELL, 0);
  ledcWriteTone(CHANELL,NOTE_AS4);
  delay(HALF);
  ledcWriteTone(CHANELL, 0);
  ledcWriteTone(CHANELL,NOTE_AS4);
  delay(HALF);    
  ledcWriteTone(CHANELL, 0);
  ledcWriteTone(CHANELL,NOTE_AS4);
  delay(WHOLE);
  delay(25);
  ledcWriteTone(CHANELL, 0);
  ledcWriteTone(CHANELL,NOTE_AS4);
  delay(HALF);  
  ledcWriteTone(CHANELL, 0);  
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(HALF);
  ledcWriteTone(CHANELL, 0);
  ledcWriteTone(CHANELL,NOTE_A4);
  delay(WHOLE);
 
  ledcWriteTone(CHANELL,NOTE_C5);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_C5);
  delay(HALF);    
  ledcWriteTone(CHANELL,NOTE_AS4);
  delay(HALF);
  ledcWriteTone(CHANELL,NOTE_G4);
  delay(HALF);    
  ledcWriteTone(CHANELL,NOTE_F4);
  delay(HALF+WHOLE);
  ledcWriteTone(CHANELL, 0);
      
  vTaskDelete(NULL);
}
 
void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }
 
  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}
 
void playSnow(void *pvParameters){
     //snow flakes
    testdrawbitmap(snowFlake, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);  
}
 
void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //display.display();
  delay(2000);
  display.clearDisplay();
 
  // invert the display
  display.invertDisplay(true);
  delay(1000); 
  display.invertDisplay(false);
  delay(1000); 
  display.clearDisplay();
  
  gpio_set_direction(BUZZER_PIN,GPIO_MODE_INPUT);
  ledcSetup(CHANELL, FREQUENCE, RESOLUTION);
  ledcAttachPin(BUZZER_PIN, CHANELL);
  
  xTaskCreatePinnedToCore(jingleBell,"jingleBell",8192,NULL,10,NULL,0);
  xTaskCreatePinnedToCore(playSnow,"playSnow",8192,NULL,10,NULL,0);
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
 
}
