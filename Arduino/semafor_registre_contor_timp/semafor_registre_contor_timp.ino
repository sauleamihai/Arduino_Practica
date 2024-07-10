#define PIN0 0

#define PIN_RED_PIETONI 2
#define PIN_GREEN_PIETONI 3
#define PIN_GREEN_MASINI 1
#define PIN_RED_MASINI 5

byte stareLedRM = 0;
byte stareLedRP = 1;
byte stareLedGM = 1;
byte stareLedGP = 0;

byte modificareStare(byte stare, byte PIN) {
  stare = !stare;
  PORTB &= ~(1 << PIN);
  PORTB |= stare << PIN;
  return stare;
}

void setup() {
  DDRB = (0 << PIN0) | (1 << PIN_RED_MASINI) | (1 << PIN_RED_PIETONI) | (1 << PIN_GREEN_PIETONI) | (1 << PIN_GREEN_MASINI);
  PORTB = (stareLedRP << PIN_RED_PIETONI) | (stareLedGP << PIN_GREEN_PIETONI) | (stareLedGM << PIN_GREEN_MASINI) | (stareLedRM << PIN_RED_MASINI) | (1 << PIN0);
}

void loop() {
  unsigned long timp_curent = millis();
  static unsigned long contor_masini = 0;
  static unsigned long contor_pietoni = 0;
  static bool buttonPressed = false;

  if ((PINB & (1 << PIN0)) == 0) {
    delay(500);
    if (!buttonPressed) {
      buttonPressed = true;
      contor_pietoni = timp_curent + 30000;
      contor_masini = timp_curent + 30000;
      stareLedRM = modificareStare(stareLedRM, PIN_RED_MASINI);
      stareLedRP = modificareStare(stareLedRP, PIN_RED_PIETONI);
      stareLedGM = modificareStare(stareLedGM, PIN_GREEN_MASINI);
      stareLedGP = modificareStare(stareLedGP, PIN_GREEN_PIETONI);
    }
    while ((PINB & (1 << PIN0)) == 0) {
      
    }
  }

  if (timp_curent > contor_masini && contor_masini != 0) {
    stareLedRM = modificareStare(stareLedRM, PIN_RED_MASINI);
    stareLedGM = modificareStare(stareLedGM, PIN_GREEN_MASINI);
    contor_masini = 0; // reset the counter
    buttonPressed = false;
  }

  if (timp_curent > contor_pietoni && contor_pietoni != 0) {
    stareLedRP = modificareStare(stareLedRP, PIN_RED_PIETONI);
    stareLedGP = modificareStare(stareLedGP, PIN_GREEN_PIETONI);
    contor_pietoni = 0;
    buttonPressed = false;
  }
}
