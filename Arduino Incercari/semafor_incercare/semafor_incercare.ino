#define LED_RED_PIETONI 4
#define LED_GREEN_PIETONI 3
#define LED_RED_MASINI 6
#define LED_GREEN_MASINI 5
#define PUSH_BUTTON 7

byte lastButtonState;
byte ledStateRedMasini = LOW;
byte ledStateGreenMasini = HIGH;
byte ledStateRedPietoni = HIGH;
byte ledStateGreenPietoni = LOW;

unsigned long lastTimeButtonChanged = 0;
unsigned long debounceTime = 100;
unsigned long changeTime = 7000; // 2 seconds for LED change
unsigned long lastChangeTime = 0;
bool changeInProgress = false;

void setup() {
  pinMode(LED_RED_PIETONI, OUTPUT);
  pinMode(LED_GREEN_PIETONI, OUTPUT);
  pinMode(LED_RED_MASINI, OUTPUT);
  pinMode(LED_GREEN_MASINI, OUTPUT);
  pinMode(PUSH_BUTTON, INPUT);
  lastButtonState = digitalRead(PUSH_BUTTON);

  // Set initial states
  digitalWrite(LED_RED_PIETONI, ledStateRedPietoni);
  digitalWrite(LED_GREEN_PIETONI, ledStateGreenPietoni);
  digitalWrite(LED_RED_MASINI, ledStateRedMasini);
  digitalWrite(LED_GREEN_MASINI, ledStateGreenMasini);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastTimeButtonChanged >= debounceTime) {
    byte buttonState = digitalRead(PUSH_BUTTON);
    if (buttonState != lastButtonState) {
      lastTimeButtonChanged = currentTime;
      lastButtonState = buttonState;
      if (buttonState == LOW) { // Button pressed
        if (!changeInProgress && ledStateRedMasini == LOW && ledStateGreenMasini == HIGH && ledStateRedPietoni == HIGH && ledStateGreenPietoni == LOW) {
          ledStateRedMasini = HIGH;
          ledStateGreenMasini = LOW;
          ledStateRedPietoni = LOW;
          ledStateGreenPietoni = HIGH;
          
          // Update LED states
          digitalWrite(LED_RED_MASINI, ledStateRedMasini);
          digitalWrite(LED_GREEN_MASINI, ledStateGreenMasini);
          digitalWrite(LED_RED_PIETONI, ledStateRedPietoni);
          digitalWrite(LED_GREEN_PIETONI, ledStateGreenPietoni);
          
          lastChangeTime = currentTime;
          changeInProgress = true;
        }
      }
    }
  }

  if (changeInProgress && currentTime - lastChangeTime >= changeTime) {
    ledStateRedMasini = LOW;
    ledStateGreenMasini = HIGH;
    ledStateRedPietoni = HIGH;
    ledStateGreenPietoni = LOW;
    
    // Update LED states again
    digitalWrite(LED_RED_MASINI, ledStateRedMasini);
    digitalWrite(LED_GREEN_MASINI, ledStateGreenMasini);
    digitalWrite(LED_RED_PIETONI, ledStateRedPietoni);
    digitalWrite(LED_GREEN_PIETONI, ledStateGreenPietoni);

    changeInProgress = false;
  }
}
