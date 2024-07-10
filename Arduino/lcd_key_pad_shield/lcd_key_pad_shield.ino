#include <LiquidCrystal.h>

// LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 

LiquidCrystal lcd(pin_RS, pin_EN, pin_d4, pin_d5, pin_d6, pin_d7);
int score = 0;

byte DinoChar[] = {
  B00100,
  B01110,
  B11111,
  B10101,
  B11111,
  B01110,
  B01010,
  B01010
};

byte obstacle[] = {
  B01110,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01110
};

int dinoPos = 0; 
int obstaclePos = 15; 
bool isJumping = false; 

unsigned long lastMoveTime = 0; 
unsigned long jumpStartTime = 0; 
const unsigned long moveInterval = 300; 
const unsigned long jumpDuration = 600; 

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, DinoChar);
  lcd.createChar(1, obstacle);
  lcd.setCursor(0, 1);
  lcd.write((byte)0); 
  lcd.setCursor(0, 0);
  lcd.print("Press Up to Jump");
}

void loop() {
  unsigned long currentTime = millis();
  int x = analogRead(0);

  
  if (x < 200 && x >= 60 && !isJumping) {
    isJumping = true;
    jumpStartTime = currentTime;
  }

  
  if (isJumping && currentTime - jumpStartTime > jumpDuration) {
    isJumping = false;
  }

  dinoPos = isJumping ? 1 : 0;

  if (currentTime - lastMoveTime > moveInterval) {
    lastMoveTime = currentTime;
    obstaclePos--;
    if (obstaclePos < 0) {
      obstaclePos = 15; 
      score++; 
    }
  }

  
  lcd.clear();

  
  lcd.setCursor(5, 0);
  lcd.print("Score:");
  lcd.setCursor(11, 0);
  lcd.print(score);

  lcd.setCursor(0, 1 - dinoPos);
  lcd.write((byte)0);


  if (obstaclePos < 16) {
    lcd.setCursor(obstaclePos, 1);
    lcd.write((byte)1);
  }

  
  if (obstaclePos == 0 && dinoPos == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Game Over!");
    while (true); 
  }

  delay(50); 
}
