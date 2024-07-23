#include <LiquidCrystal.h>

const byte RS = 11, EN = 12;
const byte DB4 = 4, DB5 = 5, DB6 = 6, DB7 = 7;
LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

int contor = 0;
int secunde = 0;
int minute = 0;
int ore = 0;

void setup() {
    lcd.begin(16, 2);
    lcd.print("ORA EXACTA:");
    
    DDRD |= (1 << 2) | (1 << 3);
    
    EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0) | (1 << INT1);
    EIFR &= ~((1 << INTF1) | (1 << INTF0));
    
    TCCR0A = (1 << WGM01);
    OCR0A = 0xF9;
    TIMSK0 |= (1 << OCIE0A);
    
    TCCR0B = (1 << CS02) | (1 << CS01) | (1 << CS00);
    
    SREG |= (1 << SREG_I);
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

ISR(TIMER0_COMPA_vect) {
    SREG &= ~(1 << SREG_I);
    ++contor;
    if (contor >= 250) {
        ++secunde;
        contor = 0;
        if (secunde >= 60) {
            incrementMinute();
            secunde %= 60;
        }
    }
    SREG |= (1 << SREG_I);
}

ISR(INT0_vect) {
    SREG &= ~(1 << SREG_I);
    incrementMinute();
    SREG |= (1 << SREG_I);
}

ISR(INT1_vect) {
    SREG &= ~(1 << SREG_I);
    incrementOre();
    SREG |= (1 << SREG_I);
}
