#include <LiquidCrystal.h>
#include <math.h> // Include math.h for the pow function

#define ADC_VREF_TYPE ((1 << REFS0) | (0 << ADLAR))

LiquidCrystal lcd(10, 9, 4, 5, 6, 7);
float stepADC = 5.0 / 1024.0;
int RL_VALUE = 5; 
float RO_CLEAN_AIR_FACTOR = 9.83; 
int CALIBRATION_SAMPLE_TIMES = 50;
int CALIBRATION_SAMPLE_INTERVAL = 500;
int READ_SAMPLE_INTERVAL = 50;
int READ_SAMPLE_TIMES = 5;

#define GAS_LPG 0
#define GAS_CO 1
#define GAS_SMOKE 2

float LPGCurve[3] = {2.3, 0.21, -0.47};
float COCurve[3] = {2.3, 0.72, -0.34}; 
float SmokeCurve[3] = {2.3, 0.53, -0.44}; 
float Ro = 10; // Ro value


float MAX_PPM_LPG = 10000; 
float MAX_PPM_CO = 1000; 
float MAX_PPM_SMOKE = 1290000999; 

void setup() {
  lcd.begin(16, 2); 
  initializareADC(); 
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Smoke Persantage ");
  lcd.setCursor(0, 1);
  
  unsigned int sensorValue = citesteADC(5); 
  float rs = MQResistanceCalculation(sensorValue);
  float iPPM_Smoke = MQGetGasPercentage(rs / Ro, GAS_SMOKE); 
  
  // Convert PPM to percentage
  float percentageSmoke = (iPPM_Smoke / MAX_PPM_SMOKE) * 100;
  
  lcd.print(percentageSmoke, 2); 
  lcd.print("%");
  delay(100);
  lcd.clear(); 
}

unsigned int citesteADC(unsigned char adc_input) {
  ADMUX = adc_input | ADC_VREF_TYPE;
  delayMicroseconds(10);
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC)) {} 
  return ADCW;
}

void initializareADC() {
  DIDR0 = 0x00; 
  ADMUX = ADC_VREF_TYPE;
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
}

long MQGetGasPercentage(float rs_ro_ratio, int gas_id) {
  if (gas_id == GAS_LPG) {
    return MQGetPercentage(rs_ro_ratio, LPGCurve);
  } else if (gas_id == GAS_CO) {
    return MQGetPercentage(rs_ro_ratio, COCurve);
  } else if (gas_id == GAS_SMOKE) {
    return MQGetPercentage(rs_ro_ratio, SmokeCurve);
  }
  return 0;
}

long MQGetPercentage(float rs_ro_ratio, float *pcurve) {
  return (pow(10, (((log(rs_ro_ratio) - pcurve[1]) / pcurve[2]) + pcurve[0])));
}

float MQResistanceCalculation(int raw_adc) {
  return ((float)RL_VALUE * (1023 - raw_adc) / raw_adc);
}
