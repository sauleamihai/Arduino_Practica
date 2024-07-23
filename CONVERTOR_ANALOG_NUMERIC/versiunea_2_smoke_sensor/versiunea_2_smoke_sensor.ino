#include <LiquidCrystal.h>
#define ADC_VREF_TYPE ((1<<REFS0)|(0<<ADLAR))
#define N_modes 7
#define max_moist 798
#define PIN_LED_RED 2
#define PIN_LED_GREEN 1
#define max_bend 2
#define ButtonPinD 2 
#define TurnOnMoisture 0

int previousMoist = 0;
int resetareAD = 0;
int contor_mode = 1;
unsigned int bend_prag=5;
unsigned int moist_prag=798;
unsigned int temp_prag=200;
int previous_state_leds=0;
unsigned int bend;
unsigned int moist;
unsigned int temp;
LiquidCrystal lcd(12, 11, 5, 4, 8, 7);
float stepADC = 5.0 / 1024.0; // Calculate step based on Vref

void resetareADMUX() {
  ADMUX &= ~((1 << REFS0) | (1 << REFS1) | (1 << ADLAR) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
}

void afisare_lcd(int counter) {
  lcd.clear(); // Clear the LCD before printing new content

  if (resetareAD == 0) {
    resetareADMUX();
    resetareAD = 1;
    initializareADC();
  }

  if (counter == 0) {
    PORTD &= ~(1 << TurnOnMoisture);
    ADMUX |= (1 << REFS1) | (1 << REFS0);
    lcd.print("procent baterie");
    lcd.setCursor(0, 1);
    ADMUX = (ADMUX & 0xF0) | (1 << MUX2);
    ADCSRA |= (1 << ADSC);
    while (bit_is_set(ADCSRA, ADSC));
    uint16_t adcValue = ADC;
    float adcVoltage = adcValue * (1.1 / 1023.0);
    float batteryVoltage = adcVoltage * (6.2 + 3.6) / 3.6;
    lcd.print(batteryVoltage);
    lcd.print(" V");

    // Debug output to Serial Monitor
    Serial.print("Mode: ");
    Serial.print(counter);
    Serial.print(" | Battery Voltage: ");
    Serial.println(batteryVoltage);

    delay(1000);
  } else if (counter == 1) {
    lcd.print("TEMPERATURA");
    lcd.setCursor(0, 1);
    unsigned int sensorValue = citesteADC(0);
    float tensiune = stepADC * sensorValue;
    float temperatura = (stepADC * sensorValue - 0.5) * 100;
    temp=temperatura;
    lcd.print(temperatura, 3);

    // Debug output to Serial Monitor
    Serial.print("Mode: ");
    Serial.print(counter);
    Serial.print(" | Temperature: ");
    Serial.println(temperatura);

    delay(1000);
  } else if (counter == 2) {
    PORTD |= (1 << TurnOnMoisture);
    lcd.print("MOISTURE");
    lcd.setCursor(0, 1);
    unsigned int sensorValue = citesteADC(1);
    float moisture = sensorValue;
    moist=moisture;
    lcd.print(moisture, 3);

    // Debug output to Serial Monitor
    Serial.print("Mode: ");
    Serial.print(counter);
    Serial.print(" | Moisture: ");
    Serial.println(moisture);

    delay(1000);
  } else if (counter == 3) {
    lcd.print("BEND");
    lcd.setCursor(0, 1);
    unsigned int sensorValue1 = citesteADC(2);
    unsigned int sensorValue2 = citesteADC(3);
    float bend_val = (sensorValue1 + sensorValue2) / 2;
    bend=bend_val;
    lcd.print(bend_val, 3);

    // Debug output to Serial Monitor
    Serial.print("Mode: ");
    Serial.print(counter);
    Serial.print(" | BEND: ");
    Serial.println(bend_val);

    delay(1000);
  }else if (counter==4){
  lcd.print("BEND PRAG");
    lcd.setCursor(0, 1);
    bend_prag=citesteADC(5);
    int mappedBend = map(bend_prag, 0, 1023, 6, 33);
    bend_prag=mappedBend;
    lcd.print(mappedBend);
    Serial.print("Mode: ");
    Serial.print(counter);
    Serial.print(" | BEND_PRAG: ");
    Serial.println(bend_prag);
    delay(1000);
  }
  else if(counter==5){
  lcd.print("TEMP PRAG");
    lcd.setCursor(0, 1);
    temp_prag=citesteADC(5);
    int mappedTemp = map(temp_prag, 0, 1023, -40, 124);
    temp_prag=mappedTemp;
    lcd.print(mappedTemp);
    Serial.print("Mode: ");
    Serial.print(counter);
    Serial.print(" | TEMP_PRAG: ");
    Serial.println(temp_prag);
    delay(1000);
  }
  else if(counter==6){
  lcd.print("MOIST PRAG");
    lcd.setCursor(0, 1);
    moist_prag=citesteADC(5);
    int mappedMoist = map(moist_prag, 0, 1023, 0, 798);
    moist_prag=mappedMoist;
    lcd.print(mappedMoist);
    Serial.print("Mode: ");
    Serial.print(counter);
    Serial.print(" | MOIST_PRAG: ");
    Serial.println(moist_prag);
    delay(1000);
  }
  
}

void setup() {
  lcd.begin(16, 2); // Corrected the order of arguments for the function call
  initializareADC();
  Serial.begin(9600);
  DDRD &= ~(1 << ButtonPinD); 
  EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);
  EIMSK |= (1 << INT0) | (1 << INT1);
  EIFR |= (0 << INTF0) | (1 << INTF1);
  DDRD |= (1 << TurnOnMoisture);
  PORTD &= ~(1 << TurnOnMoisture);
  DDRB|=(1<< PIN_LED_RED )|(1<< PIN_LED_GREEN);
  PORTB|=(0<< PIN_LED_RED)|(1<<PIN_LED_GREEN);
}

void loop() {
  afisare_lcd(contor_mode);
  if((bend<bend_prag || temp>temp_prag || moist>moist_prag) && previous_state_leds ==0){
  previous_state_leds =1;
    PORTB |=(1<< PIN_LED_RED);
    PORTB &=~(1<< PIN_LED_GREEN);
  }else if((bend>bend_prag && temp<temp_prag && moist<moist_prag)&& previous_state_leds ==1){
  previous_state_leds =0;
    PORTB |=(1<< PIN_LED_GREEN);
    PORTB &=~(1<< PIN_LED_RED);
  }
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
  ADMUX = ADC_VREF_TYPE | (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler 128
}

ISR(INT0_vect) {
  // No need to use cli() and sei() here as ISR disables interrupts by default
  if (contor_mode < N_modes - 1) {
    ++contor_mode;
  } else {
    contor_mode = 0;
  }
  resetareAD = 0;
  // Debug output to Serial Monitor
  Serial.print("ISR triggered | New Mode: ");
  Serial.println(contor_mode);

  afisare_lcd(contor_mode);
}

ISR(INT1_vect){
  if(contor_mode>0){
  --contor_mode;
  }else{
  contor_mode=0;
  }
}
