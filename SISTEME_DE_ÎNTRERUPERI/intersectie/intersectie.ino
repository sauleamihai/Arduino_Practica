#define pinLedRedP_TopB 0
#define pinLedGreenP_TopB 1
#define pinLedRedM_TopB 2
#define pinLedYellowMTopB 3
#define pinLedGreenMTopB 4
#define pinButtonTopD 0
#define pinButtonBottomD 1

byte stareLedRM = 0;
byte stareLedYM = 0;
byte stareLedRP = 1;
byte stareLedGM = 1;
byte stareLedGP = 0;
static bool buttonPressed = false;

byte modificareStare(byte stare, byte PIN) {
  stare = !stare;
  PORTB &= ~(1 << PIN);
  PORTB |= stare << PIN;
  return stare;
}

void setup() {
  Serial.begin(9600);
  DDRD |= (0 << pinButtonTopD) | (0 << pinButtonBottomD);  
  DDRB |= (1 << pinLedRedP_TopB) | (1 << pinLedGreenP_TopB) | (1 << pinLedRedM_TopB) | (1 << pinLedYellowMTopB) | (1 << pinLedGreenMTopB);  // Set LEDs as output
  PORTB = (stareLedRM << pinLedRedM_TopB) | (stareLedYM << pinLedYellowMTopB) | (stareLedRP << pinLedRedP_TopB) | (stareLedGM << pinLedGreenMTopB) | (stareLedGP << pinLedGreenP_TopB);
  PORTD |= (1 << pinButtonTopD) | (1 << pinButtonBottomD);  
}

void loop() {
  unsigned long timp_curent = millis();
  static unsigned long contor_masini = 0;
  static unsigned long contor_pietoni = 0;
  static unsigned long contor_yellow_pietoni = 0;
  static unsigned long contor_yellow_masini = 0;
  static unsigned long lastButtonPressTime = 0;
  const unsigned long debounceDelay = 50;

  int buttonStateTop = PIND & (1 << pinButtonTopD);
  int buttonStateBottom = PIND & (1 << pinButtonBottomD);
  Serial.println(buttonStateTop == 0 ? "Pressed (0)" : "Released (1)");
  Serial.println(buttonStateBottom == 0 ? "Pressed (0)" : "Released (1)");
  if ((buttonStateTop == 0 || buttonStateBottom == 0) && !buttonPressed && (timp_curent - lastButtonPressTime > debounceDelay)) {
    delay(50);  
    if (buttonStateTop == 0 || buttonStateBottom == 0) {
      Serial.println("Button Pressed!");
      buttonPressed = true;
      contor_masini = timp_curent + 10000;
      contor_yellow_masini = contor_masini + 1000;
      contor_pietoni = contor_yellow_masini + 20000;
      contor_yellow_pietoni = contor_pietoni + 1000;
      lastButtonPressTime = timp_curent;
      while ((PIND & ((1 << pinButtonTopD) | (1 << pinButtonBottomD))) == 0) {
        // Wait until button is released
      }
    }
  }

  if (timp_curent > contor_masini && contor_masini != 0) {
    stareLedYM = modificareStare(stareLedYM, pinLedYellowMTopB);
    stareLedGM = modificareStare(stareLedGM, pinLedGreenMTopB);
    contor_masini = 0;
  }

  if (timp_curent > contor_yellow_masini && contor_yellow_masini != 0) {
    stareLedYM = modificareStare(stareLedYM, pinLedYellowMTopB);
    stareLedRM = modificareStare(stareLedRM, pinLedRedM_TopB);
    stareLedRP = modificareStare(stareLedRP, pinLedRedP_TopB);
    stareLedGP = modificareStare(stareLedGP, pinLedGreenP_TopB);
    contor_yellow_masini = 0;
    Serial.println("Switched lights after yellow (cars)");
  }

  if (timp_curent > contor_pietoni && contor_pietoni != 0) {
    stareLedYM = modificareStare(stareLedYM, pinLedYellowMTopB);
    stareLedRM = modificareStare(stareLedRM, pinLedRedM_TopB);
    contor_pietoni=0;
  }

  if (timp_curent > contor_yellow_pietoni && contor_yellow_pietoni != 0) {
    stareLedYM = modificareStare(stareLedYM, pinLedYellowMTopB);
    stareLedGM = modificareStare(stareLedGM, pinLedGreenMTopB);
    stareLedGP = modificareStare(stareLedGP, pinLedGreenP_TopB);
     stareLedRP = modificareStare(stareLedRP, pinLedRedP_TopB);
    contor_yellow_pietoni = 0;
    buttonPressed = false;
    Serial.println("Switched lights after yellow (pedestrians)");
  }
}
