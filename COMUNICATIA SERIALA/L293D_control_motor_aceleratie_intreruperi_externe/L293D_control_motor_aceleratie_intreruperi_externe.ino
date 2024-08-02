#include <avr/io.h>
#include <avr/interrupt.h>

#define Input1 PB0  // Assuming Input1 is connected to PB0 (Pin 8 on Arduino Uno)
#define Input2 PB2  // Assuming Input2 is connected to PB2 (Pin 10 on Arduino Uno)

int contor = 0;
int contor_timp = 0;
volatile byte contor_incrementare = 0;

void setup() {
  sei();  
  DDRB |= (1 << Input1) | (1 << Input2);
  PORTB |= (1 << Input1);  // Set Input1 high
  PORTB &= ~(1 << Input2); // Set Input2 low
  
  Serial.begin(9600);  

  DDRD |= (1 << DDD2) | (1 << DDD3);  // Assuming INT0 and INT1 are connected to PD2 and PD3
  DDRB |= (1 << DDB1);  // PB1 (OC1A) as output for PWM

  // External Interrupts Configuration
  EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);  // Rising edge triggers
  EIMSK |= (1 << INT1) | (1 << INT0);  // Enable INT1 and INT0

  // Timer0 Configuration
  TCCR0A = (1 << WGM01);  // CTC mode
  OCR0A = 0xF9;  // Compare value for 125 Hz with 8 MHz clock and prescaler 256
  TIMSK0 |= (1 << OCIE0A);  // Enable compare match interrupt
  TCCR0B = (1 << CS02);  // Prescaler 256

  // Timer1 Configuration for Fast PWM 10-bit
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);
  TCCR1A |= (1 << WGM10) | (1 << WGM11);
  TCCR1A |= (1 << COM1A1);
  TCCR1A &= ~(1 << COM1A0);
  TCCR1B |= (1 << CS10) | (1 << CS11);  // Prescaler 64
  TCCR1B &= ~(1 << CS12);
  DDRB |= (1 << DDB1);  // PB1 (OC1A) as output
  OCR1A = 30;  // Initial duty cycle 0
 
}

void loop() {
}

ISR(TIMER0_COMPA_vect) {
  contor_timp++;
  if (contor_timp == 250) {
    contor_incrementare = !contor_incrementare;  // Toggle the flag
    contor_timp = 0;
  }
}

ISR(INT0_vect) {
  if (contor_incrementare == 1) {
    if (contor < 768) {
      contor += 256;
    } else {
      contor = 0;
    }
    OCR1A = contor;
    Serial.println(contor);
  }
}

ISR(INT1_vect) {
  if (contor_incrementare == 1) {
    if (contor >= 256) {
      contor -= 256;
    } else {
      contor = 0;
    }
    OCR1A = contor;
    Serial.println(contor);
  }
}
