#define LED_PIN 7
void setup() {
  // put your setup code here, to run once:
   pinMode(LED_PIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   digitalWrite(LED_PIN,HIGH);
   delay(4000);
   digitalWrite(LED_PIN,LOW);
   delay(4000);
}
