#define DDD1 1
#define PORTD1 1
#define DDD0 0
#define PORTD0 0

void setup() {
  DDRD = (1 << DDD1) | (1 << DDD0);
}

void loop() {
  PORTD = (1 << PORTD1) | (1 << PORTD0); 
  delay(1000); 
  
  PORTD &= ~(1 << PORTD1); 
  delay(1000); 
  
  PORTD &= ~(1 << PORTD0); 
  delay(1000); 
}
