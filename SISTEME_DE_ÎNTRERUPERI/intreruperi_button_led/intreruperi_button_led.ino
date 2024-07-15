#include<avr/interrupt.h>

ISR(INT0_vect)
{
 SREG&= ~(1<< SREG_I);

 if((PORTC &(1<<PC2))==0)
 {
  PORTC|=(1<<PC2);
 }
 else
 {
  PORTC&=~(1<<PC2);
 }

 SREG |=1<<SREG_I;
}
void setup()
{
  DDRC=0x00;
  PORTC=0x00;

  SREG|=(1<<SREG_I);
  EICRA=(0<<ISC11)|(0<<ISC10)|(1<<ISC01)|(1<<ISC00);
  EIMSK=(0<<INT1)|(1<<INT0);
  EIFR=(0<<INTF1)|(0<<INTF0);
  PCICR=(0<<PCIE2)|(0<<PCIE1)|(0<<PCIE0);
}

void loop()
{
}

