const byte ledPin = 5;
const byte butoonPin = 7;

volatile bool togglestate = false;

void setup() {
 DDRD|=(1<<ledPin);
 DDRB|=(1<<buttonPin);
 PORTD|=(0<<ledPin);
 PCICR|=B00000100;
 PCMSK2|=B10000000;

}

void loop() {
  // put your main code here, to run repeatedly:

}

ISR(PCINT2_vect)
{
  togglestate =!togglestate;

}
