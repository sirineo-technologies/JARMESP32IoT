

// https://sites.google.com/site/toucatronic/arduino/criando-bibliotecas
#include "jarm-class.h"

int ledPin = 2;  //LED verde
//int ledPin = 17;  //LED azul rgb jarm
//int ledPin = 27;  //LED verde rgb
//int ledPin = 16;  //LED vermelho jarm
//int ledPin = 17;  // ligado ao led azul wroombee
//int ledPin = 32 ;  // ligado ao led vermelho wroombee
int timer = 500;

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop()
{
    Serial.println("Hello world, I am Wroombee-EngeBOT! LIGA LED");
    digitalWrite(ledPin, HIGH);
    delay(timer);
    digitalWrite(ledPin, LOW);
    Serial.println("Hello world, I am Wroombee-EngeBOT! DESLIGA LED");
    delay(timer);
}
