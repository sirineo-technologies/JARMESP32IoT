// the setup function runs once when you press reset or power the board

//int tempo = 10000; // 10.000 = 1Os
//int tempo = 100000; // 100.000 = 1MIN
int tempo = 200000; // 100.000 = 2MIN

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(17, OUTPUT);
}
 
// the loop function runs over and over again forever
void loop() {
  
    digitalWrite(17, HIGH); // turn the LED on (HIGH is the voltage level)
    Serial.println("AT$GI?");
    Serial.println("AT$RC");
    Serial.println("AT$SF=42324F4E");
    Serial.println("DESLIGA LED");
    //ESP.restart(); //ESP.reset();
    delay (tempo); // wait for a second
    
    digitalWrite(17, LOW); // turn the LED off by making the voltage LOW
    Serial.println("LIGA LED");
    ESP.restart(); //ESP.reset();
    delay (tempo); // wait for a second
     
  }


