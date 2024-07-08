#include "led_functions.h"

void powerOnLED(byte pin) {
  digitalWrite(pin, HIGH);
}

void powerOffLED(byte pin) {
  digitalWrite(pin, LOW);
}

void setupLED(byte pin) {
  pinMode(pin, OUTPUT);
}

unsigned long TimePassed(unsigned long startTime) {
  unsigned long timeNow = millis();
  return timeNow - startTime;
}
