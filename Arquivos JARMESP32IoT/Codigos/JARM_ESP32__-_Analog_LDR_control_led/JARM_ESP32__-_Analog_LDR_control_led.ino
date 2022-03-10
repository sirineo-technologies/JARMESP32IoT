int pinoLED = 16;
int pinoPOT = 32;
int brilho;
 
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup () {
pinMode(pinoPOT, INPUT);
ledcSetup(ledChannel, freq, resolution);
ledcAttachPin(pinoLED, ledChannel);
Serial.begin(115200);
Serial.println("JARM ESP32 -  Analog IN/OUT Test");
}
 
void loop () {
brilho = analogRead(pinoPOT);
brilho = map(brilho, 0, 1023, 0, 255);
ledcWrite(ledChannel, brilho);
Serial.print("luminosidade=");
Serial.println(brilho);
delay(100);
}
