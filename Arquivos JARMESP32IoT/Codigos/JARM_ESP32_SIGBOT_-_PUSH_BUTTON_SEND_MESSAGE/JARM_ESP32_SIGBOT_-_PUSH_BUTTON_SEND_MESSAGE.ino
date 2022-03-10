

const int button1Pin = 35;
//const int button2Pin = 9;
int button1State = 0;
//int button2State = 0;

//const int ResetOFF = 14;


void setup() {

//digitalWrite(ResetOFF, HIGH);
pinMode(button1Pin, INPUT);
//pinMode(button2Pin, INPUT);
Serial.begin(9600);
//sigfox.begin(9600);
//Serial.println("init ok. listening..");
pinMode(17, OUTPUT);
}

void loop() {
button1State = digitalRead(button1Pin);
//button2State = digitalRead(button2Pin);

if(button1State == HIGH){
// sigfox.println("AT$SF=42314F4E");
Serial.println("AT$GI?");
Serial.println("AT$RC");
Serial.println("AT$SF=42324F4E");
//Serial.println("teste zigbee");
//Serial.println("BTN 2 ON");
//Serial.println("teste zigbee");
//Serial.println("ok");
digitalWrite(17, LOW); 
ESP.restart();
}
else {
  digitalWrite(17, HIGH); 
  ESP.restart();
  
  }

/*
if(button2State == HIGH){

sigfox.println("AT$GI?");
sigfox.println("AT$RC");
sigfox.println("AT$SF=42324F4E");
sigfox.println("teste zigbee");
Serial.println("BTN 2 ON");
Serial.println("teste zigbee");
} */

delay(3000);

}
