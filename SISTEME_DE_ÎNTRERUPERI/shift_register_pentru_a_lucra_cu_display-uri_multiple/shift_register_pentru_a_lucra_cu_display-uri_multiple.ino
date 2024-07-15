const int DS_pin = 7;
const int STCP_pin = 6;
const int SHCP_pin = 5;

int contor = 0;
unsigned long lastDebounceTime0 = 0;
unsigned long lastDebounceTime1 = 0;
const unsigned long debounceDelay = 50; 
int dec_digits[10] = {1, 79, 18, 6, 76, 36, 32, 15, 0, 4};

void setup() {
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  Serial.begin(9600);
  sei();
  EIMSK |= (1 << INT0) | (1 << INT1);
  EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);
}

void loop() {
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin, SHCP_pin, LSBFIRST, dec_digits[contor % 10]); 
  shiftOut(DS_pin, SHCP_pin, LSBFIRST, dec_digits[(contor / 10)%10]);       
  digitalWrite(STCP_pin, HIGH);
}

ISR(INT0_vect) {
  unsigned long currentTime = millis();
  if ((currentTime - lastDebounceTime0) > debounceDelay) {
    if (contor < 99) {
      contor++;
    } else {
      contor = 0;
    }
    Serial.println("INT0 triggered");
    lastDebounceTime0 = currentTime;
  }
}

ISR(INT1_vect) {
  unsigned long currentTime = millis();
  if ((currentTime - lastDebounceTime1) > debounceDelay) {
    if (contor > 0) {
      contor--;
    } else {
      contor = 0;
    }
    Serial.println("INT1 triggered");
    lastDebounceTime1 = currentTime;
  }
}
