#include <avr/io.h>
#include <avr/interrupt.h>

int contor = 0;
int contor_timp = 0;
byte contor_incrementare = 0;

void setup() {
  sei();  
  
  Serial.begin(9600);  

  DDRD |= (1 << DDD2) | (1 << DDD3);
  DDRB |= (1 << DDB1);

  EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);
  EIMSK |= (1 << INT1) | (1 << INT0);

  TCCR0A = (1 << WGM01);
  OCR0A = 0xF9;
  TIMSK0 |= (1 << OCIE0A);
  TCCR0B = (1 << CS02);

  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);
  TCCR1A |= (1 << WGM10) | (1 << WGM11);
  TCCR1A |= (1 << COM1A1);
  TCCR1A &= ~(1 << COM1A0);
  TCCR1B |= (1 << CS10) | (1 << CS11);
  TCCR1B &= ~(1 << CS12);
  DDRB |= (1 << DDB1);
  OCR1A = 0;
}

void loop() {
}

ISR(TIMER0_COMPA_vect) {
  cli();
  contor_timp++;
  if (contor_timp == 250) {
    if (contor_incrementare == 0) {
      contor_incrementare = 1;
    } else {
      contor_incrementare = 0;
    }
    contor_timp = 0;
  }
  sei();
}

ISR(INT0_vect) {
  cli();
  if (contor_incrementare == 1) {
    if (contor <= 768) {
      contor += 256;
    } else {
      contor = 0;
    }
    OCR1A = contor;
    Serial.println(contor);
  }
  sei();
}

ISR(INT1_vect) {
  cli();
  if (contor_incrementare == 1) {
    if (contor >= 256) {
      contor -= 256;
    } else {
      contor = 1024;
    }
    OCR1A = contor;
    Serial.println(contor);
  }
  sei();
}
