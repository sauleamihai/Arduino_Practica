const byte N = 3;
const byte pinIncrementare = 5;
const byte pinDecrementare = 4;
const byte pinReset = 3;
const byte pinsDisplay[3] = {0, 1, 2};

const byte starePortNumere[10] = {
  0b00111111,
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111
};

int contor = 0;

void setup() {
  DDRD = 0b11111111;
  DDRB = 0b00000111;
}

bool butonApasat(byte pin_button) {
  if ((PINB & (1 << pin_button)) == 0) {
    while ((PINB & (1 << pin_button)) == 0) {
      
    }
    return true;
  }
  return false;
}

void contor_operation() {
  if (butonApasat(pinIncrementare)) {
    ++contor;
  }
  if (butonApasat(pinDecrementare)) {
    --contor;
  }
  if (butonApasat(pinReset)) {
    contor = 0;
  }
}

void loop() {
  contor_operation();
  for (byte i = 0; i < N; i++) {
    if (i == 0) {
      PORTD = starePortNumere[(contor / 100) % 10];
    } else if (i == 1) {
      PORTD = starePortNumere[(contor / 10) % 10];
    } else if (i == 2) {
      PORTD = starePortNumere[contor % 10];
    }

    PORTB |= 0b00000111;
    PORTB &= ~(1 << pinsDisplay[i]);
    delay(20);
  }
}
