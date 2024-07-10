#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>
#define RANDURI 4
#define COLOANE 4
#define dimensiune_expresie 3

#define DDRB0 0
#define DDRB1 1
#define DDRB2 2
#define DDRB3 3

byte contor = 0;
char litera;
int seconds = 0;
Adafruit_LiquidCrystal lcd_1(0);

char valoareTasta[RANDURI][COLOANE] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

int gasireNumar(char numar){
  switch(numar){
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    default: return -1; 
  }
}

char EpresieSemn(char semn){
  switch(semn){
    case 'A': return '+';
    case 'B': return '-';
    case 'C': return '*';
    case 'D': return '/';
    default: return '?'; 
  }
}

int operatie(int numar1, int numar2, char operatie){
  switch(operatie){
    case 'A': return numar1 + numar2;
    case 'B': return numar1 - numar2;
    case 'C': return numar1 * numar2;
    case 'D': return numar1 / numar2;
    default: return 0; 
  }
}

char expresieIntrodusa[dimensiune_expresie] = {'0', '0', '0'};

byte piniRanduri[] = {9, 8, 7, 6};
byte piniColoane[] = {5, 4, 3, 2};

Keypad tastatura(
  makeKeymap(valoareTasta),
  piniRanduri, piniColoane,
  RANDURI, COLOANE
);

void setup()
{
  lcd_1.begin(16, 2);
  lcd_1.print("expresie:");
  DDRD = 0x00;
  DDRB = (0 << DDRB0) | (0 << DDRB1) | (1 << DDRB2) | (1 << DDRB3);
  PORTB |= 1 << PORTB3; 
}

void loop()
{
  char tastaApasata = tastatura.getKey();
  if(tastaApasata != 0){
    if(tastaApasata == '*'){
      for(byte i = 0; i < dimensiune_expresie; ++i){
        expresieIntrodusa[i] = '0';
      }
      lcd_1.setCursor(0, 1);
      lcd_1.print("                ");
      contor = 0; 
    } else {
      expresieIntrodusa[contor] = tastaApasata;
      lcd_1.setCursor(9 + contor, 0);
      if(contor == 1){
        litera = EpresieSemn(tastaApasata);
        lcd_1.print(litera);
      }
      else {
        lcd_1.print(tastaApasata);
      }
      ++contor;
      if(contor >= dimensiune_expresie){
        lcd_1.setCursor(0, 1);
        int rezultat = operatie(gasireNumar(expresieIntrodusa[0]), gasireNumar(expresieIntrodusa[2]), expresieIntrodusa[1]);
        lcd_1.print(rezultat);                          
        contor = 0; 
      }
    }
  }
}
