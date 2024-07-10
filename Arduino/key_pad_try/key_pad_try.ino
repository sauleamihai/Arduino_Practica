#include <Keypad.h>
#define DDRB0 0
#define DDRB1 1
#define DDRB2 2
#define DDRB3 3

#define PORTB2 2
#define PORTB3 3

#define dimensiune_parola 4
#define RANDURI 4
#define COLOANE 4

byte contor = 0;

char valoareTasta[RANDURI][COLOANE]= {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

const char parolaCorecta[]={'1','6','0','2'};
char parolaIntrodusa[dimensiune_parola] = {'0', '0', '0', '0'};

byte piniRanduri[]={9,8,7,6};
byte piniColoane[]={5,4,3,2};

Keypad tastatura(
  makeKeymap(valoareTasta),
  piniRanduri, piniColoane,
  RANDURI, COLOANE
);

void setup() {
  DDRD = 0x00;
  DDRB = (0<<DDRB0) | (0<<DDRB1) | (1<<DDRB2) | (1<<DDRB3);
  PORTB |= 1<<PORTB3; 
}

bool comparaParola(){
  for(byte i=0; i<dimensiune_parola; ++i){
    if(parolaCorecta[i] != parolaIntrodusa[i]){
      return false;
    }
  }
  return true;
}

void loop() {
  const char tastaApasata = tastatura.getKey();
  if(tastaApasata != 0){
    if(tastaApasata == '#'){
      for(byte i=0; i<dimensiune_parola; ++i){
        parolaIntrodusa[i] = '0';
      }
      contor = 0; 
    } else {
      parolaIntrodusa[contor] = tastaApasata;
      ++contor;
      if(contor >= dimensiune_parola){
        contor = 0; 
      }

      if(comparaParola()){
        PORTB &= ~(1<<PORTB3);
        PORTB |= 1<<PORTB2;
        delay(1000);
        PORTB |= 1<<PORTB3;
        PORTB &= ~(1<<PORTB2);
      }
    }
  }
}
