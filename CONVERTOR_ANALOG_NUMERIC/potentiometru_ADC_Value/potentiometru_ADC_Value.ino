#include <LiquidCrystal.h>
#define ADC_VREF_TYPE ((1<<REFS0)|(0<<ADLAR))

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float stepADC = 5.0 / 1024.0; // Calculate step based on Vref

void setup() {
  lcd.begin(16, 2); // Adjusted the order of arguments for correct function call
  initializareADC();
}

void loop() {
  lcd.print("LCD Display");
  lcd.setCursor(0, 1);
  unsigned int sensorValue = citesteADC(0);
  float tensiune = stepADC * sensorValue;
  lcd.print(tensiune, 2);
  delay(100);
  lcd.clear();
}

unsigned int citesteADC(unsigned char adc_input) {
  ADMUX = adc_input | ADC_VREF_TYPE;
  delayMicroseconds(10);
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC)) {} // Wait for conversion to complete
  return ADCW;
}

void initializareADC() {
  DIDR0 = 0x00; // Disable digital inputs on ADC pins
  ADMUX = ADC_VREF_TYPE;
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler 128
}
