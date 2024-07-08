#define LED_PIN1 7  // Pin for the first LED
#define LED_PIN2 6  // Pin for the second LED

unsigned long lastTimeLedBlinked = 0;
unsigned long blinkDelay = 500;
byte ledState1 = LOW;

unsigned long anotherLedBlink = 0;
unsigned long blinkDelay2 = 2000;
byte ledState2 = LOW;

void setup() {
  // Initialize the digital pins as outputs
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
}

void loop() {
  unsigned long timeNow = millis();
  
  // Handle blinking for the first LED
  if (timeNow - lastTimeLedBlinked > blinkDelay) {
    lastTimeLedBlinked = timeNow;
    ledState1 = (ledState1 == LOW) ? HIGH : LOW;
    digitalWrite(LED_PIN1, ledState1);
  }

  // Handle blinking for the second LED
  if (timeNow - anotherLedBlink > blinkDelay2) {
    anotherLedBlink = timeNow;
    ledState2 = (ledState2 == LOW) ? HIGH : LOW;
    digitalWrite(LED_PIN2, ledState2);
  }
}
