const byte N = 2;
const byte pinsDisplay[2] = {0, 1}; 

const byte starePortNumereD[10] = {
  0b11000000,
  0b10000000,
  0b11000000,
  0b11000000,
  0b10000000,
  0b01000000,
  0b01000000,
  0b11000000,
  0b11000000,
  0b11000000
};

const byte starePortNumereB[10] = {
  0b00001111,
  0b00000001,
  0b00010110,
  0b00010011,
  0b00011001,
  0b00011011,
  0b00011111,
  0b00000001,
  0b00011111,
  0b00011011
};

int contor = 0;

ISR(INT0_vect) {
  SREG &=~(1<<SREG_I);
  contor++;
   SREG |= 1<<SREG_I;
}


ISR(INT1_vect) {
   SREG &=~(1<<SREG_I);
  contor--;
   SREG |= 1<<SREG_I;
}


void setup() {
  DDRD = (1<<7)|(1<<6);
  DDRB = 0b00111111;
  DDRC = 0x00;

  SREG |= 1 << SREG_I;

  EICRA = (1 << ISC11) | (0 << ISC10) | (1 << ISC01) | (0 << ISC00);
  EIMSK = (1 << INT1) | (1 << INT0); 
  EIFR = (1<< INTF1) | (1 << INTF0); 

  PCICR = (0 << PCIE2) | (0 << PCIE1) | (0 << PCIE0);
}

void loop() {
  for (byte i = 0; i < N; i++) {
    if (i == 0) {
      PORTD = starePortNumereD[(contor / 10) % 10];
      PORTB = starePortNumereB[(contor / 10) % 10];
    } else if (i == 1) {
      PORTD = starePortNumereD[contor % 10];
      PORTB = starePortNumereB[contor % 10];
    }

    PORTC |= 0b00000011;
    PORTC &= ~(1 << pinsDisplay[i]);
    delay(50);
  }
}
