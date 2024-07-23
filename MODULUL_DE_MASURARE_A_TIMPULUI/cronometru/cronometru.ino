#include <LiquidCrystal.h>

// Pin configuration for the LCD
const byte RS = 11, EN = 12;
const byte DB4 = 4, DB5 = 5, DB6 = 6, DB7 = 7;
LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

int running = 0;
int contor = 0;
int secunde = 0;
int minute = 0;
int ore = 0;

void setup()
{
  lcd.begin(16, 2);
  lcd.print("CRONOMETRU");

  // Set pins 2 and 3 as output
  DDRD |= (1 << 2) | (1 << 3);

  // Configure external interrupts
  EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);
  EIMSK |= (1 << INT0) | (1 << INT1);
  EIFR |= (0 << INTF0) | (1 << INTF1);

  // Configure timer 1 for 100 microsecond intervals
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS11); // CTC mode, prescaler 8
  OCR1A = 200; // 100 microseconds interval (16MHz / 8 / 200 = 1000Hz)
  TIMSK1 |= (1 << OCIE1A);

  // Enable global interrupts
  sei();
}

void loop() {
  lcd.setCursor(0, 1);
  if (ore < 10) {
    lcd.print(0);
    lcd.setCursor(1, 1);
  }
  lcd.print(ore);
  lcd.setCursor(2, 1);
  lcd.print(":");
  lcd.setCursor(3, 1);
  if (minute < 10) {
    lcd.print(0);
    lcd.setCursor(4, 1);
  }
  lcd.print(minute);
  lcd.setCursor(5, 1);
  lcd.print(":");
  lcd.setCursor(6, 1);
  if (secunde < 10) {
    lcd.print(0);
    lcd.setCursor(7, 1);
  }
  lcd.print(secunde);
}

inline void incrementOre() {
  ++ore;
  if (ore >= 24) {
    ore %= 24;
  }
}

inline void incrementMinute() {
  ++minute;
  if (minute >= 60) {
    incrementOre();
    minute %= 60;
  }
}

ISR(TIMER1_COMPA_vect) {
  if (running == 0) {
    ++contor;
    if (contor >= 10000) { // 10000 * 100 microseconds = 1 second
      ++secunde;
      contor = 0;
      if (secunde >= 60) {
        incrementMinute();
        secunde %= 60;
      }
      if (minute >= 60) {
        incrementOre();
      }
      if (ore >= 24) {
        ore = 0;
        minute = 0;
        secunde = 0;
      }
    }
  }
}

ISR(INT0_vect) {
  cli();
  if (running == 0) {
    TCCR1B &= ~(1 << CS11);
    running = 1;
  } else {
    running = 0;
    TCCR1B |= (1 << CS11);
  }
  sei();
}

ISR(INT1_vect) {
  cli();
  ore = 0;
  minute = 0;
  secunde = 0;
  sei();
}
