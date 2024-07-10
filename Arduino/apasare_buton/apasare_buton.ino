#define PIN_LED 13       
#define BUTTON_PIN 8     

byte LedState = LOW;     

void setup() {
  pinMode(PIN_LED, OUTPUT);         
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  digitalWrite(PIN_LED, LedState);  
  Serial.begin(9600);               
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN); 
  Serial.print("Button State: ");
  Serial.println(buttonState);               

 
  if (buttonState == LOW) {
    delay(50); 
    
    if (digitalRead(BUTTON_PIN) == LOW) {
      
      while (digitalRead(BUTTON_PIN) == LOW) {
      }
     
      LedState = !LedState;
      digitalWrite(PIN_LED, LedState);
      Serial.print("LED State: ");
      Serial.println(LedState);              
    }
  }
}
