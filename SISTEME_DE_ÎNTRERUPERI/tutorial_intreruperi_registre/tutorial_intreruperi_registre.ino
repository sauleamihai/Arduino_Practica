void setup() {
  DDRB|=(1<<DDB5);//PB5 output
  SREG|=(1<<7);
  //sei(); prebuit funtion into arduino
  EIMSK |=(1<<INT0)|(1<<INT1);
  EICRA |=(1<<ISC11)|(1<<ISC10)|(1<<ISC01)|(1<<ISC00);
}

void loop() {
  // put your main code here, to run repeatedly:

}

ISR(INT0_vect){
PORTB|=(1<<PB5);

}//introp handler

ISR(INT1_vect){
PORTB&=(~(1<<PB5));
}
