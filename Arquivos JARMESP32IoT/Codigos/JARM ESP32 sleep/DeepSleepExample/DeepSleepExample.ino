    /////////////////////////////////////////////////////////////////
   //             ESP32 Deep Sleep Example 1             v1.00    //
  //       Get the latest version of the code here:              //
 //       http://educ8s.tv/esp32-deep-sleep-tutorial            //
/////////////////////////////////////////////////////////////////

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  3        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

int GREEN_LED_PIN = 16;
int YELLOW_LED_PIN = 17;

void setup(){

  Serial.begin(9600);
 // Serial.println("init ok. listening..");
  
  pinMode(GREEN_LED_PIN,OUTPUT);
  pinMode(YELLOW_LED_PIN,OUTPUT);
  delay(500);
  
  if(bootCount == 0) //Run this only the first time
  {
      digitalWrite(YELLOW_LED_PIN,HIGH);
      bootCount = bootCount+1;
  }else
  {
      digitalWrite(GREEN_LED_PIN,HIGH);
  }
  
  delay(5000);

  digitalWrite(GREEN_LED_PIN,LOW);
  digitalWrite(YELLOW_LED_PIN,LOW);

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void loop(){
  
      Serial.println("AT$GI?");
      Serial.println("AT$RC");
      Serial.println("AT$SF=42324F4E");  
      //Serial.println("AT$P=1");
}

