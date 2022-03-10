//int ledPin = 16;  //LED vermelho jarm esp32 iot
int ledPin = 5;  //LED verde jarm esp32 iot
//int ledPin = 17;  //LED azul jarm esp32 iot

int timer = 500;

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop()
{
    Serial.println("Hello world, eu sou JARM ESP32 IoT ! LIGA LED");
    digitalWrite(ledPin, HIGH);
    delay(timer);
    digitalWrite(ledPin, LOW);
    Serial.println("Hello world, eu sou JARM ESP32 IoT! DESLIGA LED");
    delay(timer);
}
