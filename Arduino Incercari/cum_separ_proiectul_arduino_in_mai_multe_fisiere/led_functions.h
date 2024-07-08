#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H
#include <Arduino.h>
//the header file will contain the prototypes for the functions 
void powerOnLED(byte pin);
void powerOffLED(byte pin);
void setupLED(byte pin);
unsigned long TimePassed(unsigned long startTime);
#endif