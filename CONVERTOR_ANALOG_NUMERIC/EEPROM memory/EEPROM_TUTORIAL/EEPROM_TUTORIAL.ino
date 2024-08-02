#inslude <EEPROM.h>

int brightness;

void setup() {
  Serial.begin(9600);
  // EEPROM.write(0,25);//value between 0 and 255
  float sensor_read = 7000;//stores 4 bytes of data 
  EEPROM.put(0,sensor_read);
  

}

void loop() {
  //brightness =EEPROM.read(0);
  //Serial.println(brightness);//255 default value
  EEPROM.get(0,brightness);
   Serial.println(brightness);
  delay(500);

}
