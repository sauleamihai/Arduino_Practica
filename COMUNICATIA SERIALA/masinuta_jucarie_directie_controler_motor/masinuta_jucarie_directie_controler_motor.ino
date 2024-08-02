#include <Servo.h>
#define buttonForword 2
#define buttonBackwords 4
#define buttonLeft 7
#define buttonRight 5
#define Input1M1 1
#define Input2M1 6
#define Input1M2 0
#define Input2M2 1
#define Motor1EN 3
#define Motor2EN 3
#define ADC_VREF_TYPE ((1<<REFS0)|(0<<ADLAR))

const int trigPin = 12;
const int echoPin = 13;
float stepADC = 5.0 / 1024.0;
Servo Servo1;
int servoPin = 10;
int angleServo=90;
long duration;
int distance;

void setup() {
  Servo1.attach(servoPin);
  initializareADC();
  // Set motor control pins as output
  DDRD |= (1 << Input1M1) | (1 << Input2M1) | (1 << Motor1EN);
  PORTD &= ~((1 << Input1M1) | (1 << Input2M1));  // Ensure motors are off initially

  DDRB |= (1 << Input1M2) | (1 << Input2M2) | (1 << Motor2EN)|(1<<trigPin)|(0<<echoPin);
  PORTB &= ~((1 << Input1M2) | (1 << Input2M2));  // Ensure motors are off initially

  // Configure Timer/Counter2 for PWM
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  OCR2A = 10;
  OCR2B = 10;
  Serial.begin(9600);

  // Enable pin change interrupt for PCINT2 (Port D)
  PCICR |= _BV(PCIE2);
  PCMSK2 |= _BV(buttonForword) | _BV(buttonBackwords) | _BV(buttonLeft) | _BV(buttonRight);
  Servo1.write(angleServo);
}

void resetMotors() {
  PORTD &= ~((1 << Input1M1) | (1 << Input2M1));
  PORTB &= ~((1 << Input1M2) | (1 << Input2M2));
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
}

ISR(PCINT2_vect) {
  if (PIND & (1 << buttonForword)) {
    resetMotors();
    PORTD |= (1 << Input1M1);
    PORTB |= (1 << Input1M2);
    OCR2A = 200;
    OCR2B = 200;
  } else if (PIND & (1 << buttonBackwords)) {
    resetMotors();
    PORTD |= (1 << Input2M1);
    PORTB |= (1 << Input2M2);
    OCR2A = 200;
    OCR2B = 200;
  } else if(PIND & (1 << buttonLeft)){
    angleServo=180;//problem
    Servo1.write(angleServo);
  } else if(PIND & (1 << buttonRight)){
    angleServo=0;
    Servo1.write(angleServo);
  }else {
    resetMotors();
    angleServo=90;
    Servo1.write(angleServo);
    OCR2A = 10;
    OCR2B = 10;
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
  ADMUX = ADC_VREF_TYPE;
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler 128
}
