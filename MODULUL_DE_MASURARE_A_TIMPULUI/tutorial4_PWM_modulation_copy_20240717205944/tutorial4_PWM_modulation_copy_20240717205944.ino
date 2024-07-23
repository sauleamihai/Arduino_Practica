void setup() {
  //how it works
  //aplictions voltage regulation SMPS
  //brightness ajustment of led
  //speed control of motor
  //time period 1hz 50% duty time 0.5s on & 0.5s Off 2.5 v power delevery
  //CONFIGURE output compare module of time for generating PWM waves 
  //SET MODE OF THE TIMER
  //fast pwm 10 bit mode
  TCCR1B&=~(WGM13);
  TCCR1B|=(1<<WGM12);
  TCCR1A |=(1<<WGM10)|(1<<WGM11);
  //we have two difrent types of PWM modes the inverting one COM-compare output mode PB1
  //non enverting mode
  //set the PWM mode
  TCCR1A |=(1<<COM1A1);
  TCCR1A &=~(1<<COM1A0);
  // set the prescaler for setting the PWM Frequency 
  //16Mhz/64=2500Hz
  TCCR1B |=(1<<CS10)|(1<<CS11);
  TCCR1B &=~(1<<CS12);
  //configure PB1 as output
  DDRB|=(1<<DDB1);
  //set the duty cycle 
  

}

void loop() {
  for(int i=0;i<1024;i++){
     OCR1A=i;
     delay(2);
  }
  delay(2000);
  for(int i=1023;i=>0;i++){
    OCR1A=i;
    delay(2);
  }
   delay(2000);
  
}
