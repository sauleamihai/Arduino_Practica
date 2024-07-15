#define PORTA_PIN 4
#define PORTB_PIN 5
#define PORTC_PIN 6
#define PORTD_PIN 7
#define PORTE_PIN 0
#define PORTF_PIN 1
#define PORTG_PIN 2
#define PORTDP_PIN 3

int contor = 0;
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50; 


void setup() {
 
  DDRD |= (1 << PORTA_PIN) | (1 << PORTB_PIN) | (1 << PORTC_PIN) | (1 << PORTD_PIN);
  DDRB |= (1 << PORTE_PIN) | (1 << PORTF_PIN) | (1 << PORTG_PIN) | (1 << PORTDP_PIN);

  
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  
  Serial.begin(9600);

 
  sei();

  
  EIMSK |= (1 << INT0) | (1 << INT1);

 
  EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);
}

void displayDigit(int digit) {
 
  PORTD |= (1 << PORTA_PIN) | (1 << PORTB_PIN) | (1 << PORTC_PIN) | (1 << PORTD_PIN);
  PORTB |= (1 << PORTE_PIN) | (1 << PORTF_PIN) | (1 << PORTG_PIN) | (1 << PORTDP_PIN);

  
  switch (digit) {
    case 0:
      PORTD &= ~((1 << PORTA_PIN) | (1 << PORTB_PIN) | (1 << PORTC_PIN) | (1 << PORTD_PIN));
      PORTB &= ~((1 << PORTE_PIN) | (1 << PORTF_PIN));
      break;
    case 1:
      PORTD &= ~((1 << PORTB_PIN) | (1 << PORTC_PIN));
      break;
    case 2:
      PORTD &= ~((1 << PORTA_PIN) | (1 << PORTB_PIN)  | (1 << PORTD_PIN));
      PORTB &= ~((1 << PORTE_PIN)| (1 << PORTG_PIN));
      break;
    case 3:
      PORTD &= ~((1 << PORTA_PIN) | (1 << PORTB_PIN) | (1 << PORTC_PIN) | (1 << PORTD_PIN));
      PORTB&=~((1<<PORTG_PIN));
      break;
    case 4:
      PORTD &= ~((1 << PORTB_PIN) | (1 << PORTC_PIN));
      PORTB &= ~((1 << PORTG_PIN) | (1 << PORTF_PIN));
      break;
    case 5:
      PORTD &= ~((1 << PORTA_PIN) | (1 << PORTC_PIN)  | (1 << PORTD_PIN));
      PORTB &= ~((1 << PORTF_PIN)| (1 << PORTG_PIN));
      break;
    case 6:
      PORTD &= ~((1 << PORTA_PIN) | (1 << PORTC_PIN) | (1 << PORTD_PIN));
      PORTB &= ~((1 << PORTE_PIN) | (1 << PORTF_PIN) | (1 << PORTG_PIN));
      break;
    case 7:
      PORTD &= ~((1 << PORTA_PIN) | (1 << PORTB_PIN) | (1 << PORTC_PIN));
      break;
    case 8:
      PORTD &= ~((1 << PORTA_PIN) | (1 << PORTB_PIN) | (1 << PORTC_PIN) | (1 << PORTD_PIN));
      PORTB &= ~((1 << PORTE_PIN) | (1 << PORTF_PIN) | (1 << PORTG_PIN));
      break;
    case 9:
      PORTD &= ~((1 << PORTA_PIN) | (1 << PORTB_PIN) | (1 << PORTC_PIN));
      PORTB &= ~((1 << PORTF_PIN) | (1 << PORTG_PIN));
      break;
  }
}

void loop() {
  
  displayDigit(contor);

  
  Serial.print("Current value of contor: ");
  Serial.println(contor);

  
  delay(500);
}

ISR(INT0_vect) {
  unsigned long currentTime = millis();
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    
    if (contor < 9) {
      contor++;
    } else {
      contor = 0;
    }
    Serial.println("INT0 triggered");
    lastDebounceTime = currentTime;
  }
}

ISR(INT1_vect) {
  unsigned long currentTime = millis();
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    
    contor = 0;
    Serial.println("INT1 triggered");
    lastDebounceTime = currentTime;
  }
}
