// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}
 
// the loop function runs over and over again forever
void loop() {
  int i;
  
  for(i=0;i<2;i++)
  {
    digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.println("AT$GI?");
    Serial.println("AT$RC");
    Serial.println("AT$SF=42324F4E");
    delay(5000);                       // wait for a second
    
    digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
    delay(5000);                       // wait for a second
    Serial.print("count");
    Serial.println(i);
 
    if(i==1)
    {
      Serial.println("Resetting ESP");
       ESP.restart(); //ESP.reset();
    }
  }
}


