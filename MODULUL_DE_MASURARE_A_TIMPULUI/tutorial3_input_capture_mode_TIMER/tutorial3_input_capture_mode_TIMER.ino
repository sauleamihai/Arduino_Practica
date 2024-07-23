//aceleasi calcule ca inainte 
//time period =64us
// 0   1   2   3   4    5    6   7    8    9
// _____   RE________________RE(rising edge)
//regisrtrul IC Capture registe = 2   6
//diferance=6-2=4
//time period=4x64=256us
//FREQ =1/256us=3906.5Hz
//whenever the rising edge pulse occur at input capture pin of timer a capture interupt 
//will be taking place 
//the only capture register conf pin is PB0 
//daca rezolutia este de 100 microsecunde calculu decurge astfel
//16MHZ/8biti =2mMz
//1/2MHz=0.5microsecunde
//100microsecunde/0.5microsecunde =200
void setup() {
 //enable the global interupt enable bit 
  sei();
 //enable the required timer interupt
  TIMSK1|=(1<<ICIE1);
  //set the mode for the timer 
  TCCR1A &=(~(1<<WGM10) & (~(1<<WGM11)));
  TCCR1A &=(~(1<<WGM12) & (~(1<<WGM13)));//NORMAL MODE
  //set the prescaler for the timer
  TCCR1B |=(1<<CS12)|(1<<CS10);
  TCCR1B&=(~(1<<CS11)); //1024
  //iv
  TCNT1=0;
  //select the edge for capture 
  TCCR1B|=(1<<ICES1); //RISING EDGE CAPTURE 

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
unsigned int captured;
ISR(TIMER1_CAPT_vect){
 captured = ICR1;
  Serial.print('captured');
 Serial.print('\n');
}
