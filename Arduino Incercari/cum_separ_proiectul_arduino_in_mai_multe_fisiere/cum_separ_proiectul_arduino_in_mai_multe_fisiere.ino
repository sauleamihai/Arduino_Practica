#define LED_PIN 13
#include "led_functions.h"
unsigned long startTime;
unsigned long delayTime = 2000; // equals 2 seconds
byte previousLedState;


void setup() {
  setupLED(LED_PIN);
  startTime = 0;
  previousLedState = HIGH;
  powerOnLED(LED_PIN);
}


void loop() {
  unsigned long timeNow = millis();
  if (TimePassed(startTime) >= delayTime) {
    startTime = timeNow;
    if (previousLedState == HIGH) {
      powerOffLED(LED_PIN);
      previousLedState = LOW;
    } else {
      powerOnLED(LED_PIN);
      previousLedState = HIGH;
    }
  }
}
