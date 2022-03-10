// ESP32 Touch Test
// Just test touch pin - Touch7 is T7 which is on GPIO 27.

int ledPin = 16;

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("JARM ESP32 - Touch Test");
}

void loop()
{
  Serial.println(touchRead(T7));  // get value using T7
  if ((touchRead(T5))>50){
    Serial.println("SEM TOQUE NA JARM");
    digitalWrite(ledPin, HIGH);
  }
  else{
    Serial.println("TOQUE NA JARM");
    digitalWrite(ledPin, LOW);
  }
  delay(500);
}
