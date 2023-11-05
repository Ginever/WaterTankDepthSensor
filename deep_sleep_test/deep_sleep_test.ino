#define LED 4


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  //digitalWrite(LED, HIGH);
  
  while(!Serial) { }
  //delay(10);

  //digitalWrite(LED, LOW);
  
  Serial.println("I'm awake.");

  Serial.println("Going into deep sleep for 20 seconds");
  //ESP.deepSleep(20e6); // 20e6 is 20 microseconds
}

void loop() {
digitalWrite(LED_BUILTIN, HIGH);
delay(1000);
digitalWrite(LED_BUILTIN, LOW);
delay(1000);
}
