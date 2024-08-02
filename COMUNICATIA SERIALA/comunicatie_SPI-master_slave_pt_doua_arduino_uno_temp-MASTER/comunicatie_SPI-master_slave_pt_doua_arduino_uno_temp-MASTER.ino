#define MISO 12
#define MOSI 11
#define PIN_CLOCK 13
#define CHIP_SELECT 10

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

int receivedTemperature;
bool newDataReceived = false;

void setup_pins() 
{
  DDRB &= ~((1 << 2) | (1 << 3) | (1 << 5));
  DDRB |= (1 << 4);
  DDRD = (0 << 2) | (0 << 3);
}

bool readPin(int pin) 
{
  return PINB & (1 << (pin - 8));
}

byte receive_byte() 
{
  byte receivedByte = 0;
  for (int i = 0; i < 8; i++) {
    while (!readPin(PIN_CLOCK));
    receivedByte |= readPin(MOSI) << (7 - i);
    while (readPin(PIN_CLOCK));
  }
  return receivedByte;
}

void receive_data() {
  byte highByte, lowByte;
  if (!readPin(CHIP_SELECT)) {
    highByte = receive_byte();
    lowByte = receive_byte();
    receivedTemperature = (highByte << 8) | lowByte;
    newDataReceived = true;
  }
}

void setup() {
  Serial.begin(9600);
  setup_pins();
  lcd.init();
  lcd.backlight();
  lcd.display();
}

void loop() {
  receive_data();
  if (newDataReceived) {
    Serial.print("Received current temp: ");
    Serial.print(receivedTemperature);
    Serial.print(char(176));
    Serial.println("C");
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    lcd.print(receivedTemperature);
    lcd.print(char(176));
    lcd.print("C");
    newDataReceived = false;
  }
}
