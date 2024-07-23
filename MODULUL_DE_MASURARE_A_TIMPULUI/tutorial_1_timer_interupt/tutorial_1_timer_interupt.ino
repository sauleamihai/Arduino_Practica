void setup() {

  DDRB|=(1<<DDB5);
 //enable the global interupt enable bit
 sei();
 //enable the requiered timer interupt
 TIMSK1|=(1<<TOIE);
 //set  mode of the timer (normal mode) in this case 
 TCCR1A &=(~(1<<WGM10)) &(~(1<<WGM11));
  TCCR1B &=(~(1<<WGM12)) &(~(1<<WGM13));
  //set the prescale for the timer
  TCCR1B|=(1<<CS12)|(1<<CS10);
  TCCR1B&=~(1<<CS11)          //PRESCALAR=1024
  //set the period of the timer 
  //system clock is 16 MHZ
  //16000000/1024=15625HZ
  //1/15625=64 usec to take one step 
  //1000ms/64us=15625 counts to rech 1 sec
  //65535-15625=49910
  TCNT1=49910; //1 second

  

}

void loop() {
  // put your main code here, to run repeatedly:

}

 //impelment the interupt handler
 ISR(TIMER1_OVF_vect){
  PORTB^=(1<<PB5);//fluctueza intre high si low 
  TCNT1=49910;
 }