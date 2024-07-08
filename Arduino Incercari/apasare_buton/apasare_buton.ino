#define LED_PIN 8
#define BUTTON_PIN 7

byte lastButtonState;
byte ledState = LOW;
unsigned long lastTimeButtonChanged = 0;
unsigned long debounceDuration = 50;

void setup() {
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  // Initialize the button pin as an input
  pinMode(BUTTON_PIN, INPUT);
  lastButtonState = digitalRead(BUTTON_PIN);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastTimeButtonChanged >= debounceDuration) {
    byte buttonState = digitalRead(BUTTON_PIN);
    if (buttonState != lastButtonState) {
      lastTimeButtonChanged = currentTime;
      lastButtonState = buttonState;
      if (buttonState == LOW) {
        ledState = (ledState == HIGH) ? LOW : HIGH;
        digitalWrite(LED_PIN, ledState);
      }
    }
  }
}
