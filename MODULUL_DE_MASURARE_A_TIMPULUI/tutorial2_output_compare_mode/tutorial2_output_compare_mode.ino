void setup() {
  //generate pulses of required frequency
  //frequency of timer 15625Hz
  //timer period 1/freq=64us -time period
  //OC-output control
  //Compare register preprogramed value 
  // TIMER 0 1 2 3 
  //Copare register 2
  //oc ocilează între high si low atunci cand timerul ajunge la 2
  //configurare

  //enable the global interupt enable bit 
  sei();
  //enable the required timer interupt
  TIMSK1|=(1<<OCIE1A);
  //set the mode for the timer 
  TCCR1A &=(~(1<<WGM10) & (~(1<<WGM11)));
  TCCR1A &=(~(1<<WGM12) & (~(1<<WGM13)));//NORMAL MODE
  //set the compare output mode
  TCCR1A|=(1<<COM1A0);
  TCCR1A &=(~(1<<COM1A1));
  //set the prescaler for the timer
  TCCR1B |=(1<<CS12)|(1<<CS10);
  TCCR1B&=(~(1<<CS11));
  //start the timer with initial value 
  TCNT1 = 0;
  //load the period value for the timer 
  //system clock 16MHZ
  //the clock frequency becomes 16000000/1024=15626
  //timer for each tick 1/15625=64usec
  //1000ms/64us=15625 the count value of the timer for 1 second delay 
  OCR1A=15625;
  //configure the output compare pin as iesire 
  DDRB |= (1<<DDB1);

}

void loop() {
  // put your main code here, to run repeatedly:

}

ISR(TIMER1_COMPA_vect){
TCNT=0;
OCR1A =15625;


}
