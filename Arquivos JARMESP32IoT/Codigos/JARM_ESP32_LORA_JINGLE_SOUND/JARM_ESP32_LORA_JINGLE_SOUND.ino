int freq = 2000;
int channel = 0;
int resolution = 8;
  
void setup() {
  
 // Serial.begin(115200);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(26, channel);
  
}

void loop() {
    
     ledcWriteTone(channel, 1005);
     delay(1000);
     ledcWriteTone(channel, 1255);
     delay(1000);
     ledcWriteTone(channel, 1505);
     delay(1000);
     //ledcWriteTone(channel, 0);
}
  

