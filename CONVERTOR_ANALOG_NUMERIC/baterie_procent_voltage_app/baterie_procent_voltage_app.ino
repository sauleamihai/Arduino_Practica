#include <LiquidCrystal.h>

LiquidCrystal lcd(3,2,4,5,6,7);
void setup() {
  
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("procent baterie");
  ADMUX |= (1 << REFS1) | (1 << REFS0); 
}

void loop() {
  lcd.setCursor(0,1);
  
  
  ADMUX = (ADMUX & 0xF0) | (1 << MUX2); 
 
  ADCSRA |= (1 << ADEN) | (1 << ADSC);
  
  while (bit_is_set(ADCSRA, ADSC));

  
  uint16_t adcValue = ADC;

 
  float adcVoltage = adcValue * (1.1 / 1023.0);

  
  float batteryVoltage = adcVoltage * (6.2 + 3.6) / 3.6;
  

  
  lcd.print(batteryVoltage);
  lcd.print(" V");

  
  delay(1000);
}
