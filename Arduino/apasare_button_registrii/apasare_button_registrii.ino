#define PIN0 0

#define PIN5 5

byte stareLed=0;

void setup(){
  DDRB=(0<<PIN0) | (1<<PIN5);
  PORTB=(stareLed<<PIN5)|(1<<PIN0);

}

void loop(){
  if((PINB & (1<<PIN0))==0){
    delay(500);
    while((PINB & (1<<PIN0))==0){

    }
  
  stareLed=!stareLed;
  PORTB&=~(1<<PIN5);
  PORTB |= stareLed << PIN5;
  }
}