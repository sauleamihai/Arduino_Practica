#include <EEPROM.h>   
template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
  const byte* p = (const byte*)(const void*)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++)
    EEPROM.write(ee++, *p++);
    return i;
}
template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}
template <class T> 
int EEPROM_updateAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.update(ee++, *p++);
    return i;
}
void setup() {
  Serial.begin(9600);               
  EEPROM_writeAnything(0, 1200);  
  EEPROM_writeAnything(5, 2000);   
}


void loop() {
  int my_value_1, my_value_2;
  EEPROM_readAnything(0, my_value_1); 
  EEPROM_readAnything(5, my_value_2);
  Serial.print("Value 1: "); 
  Serial.print(my_value_1);          
  Serial.print("    Value 2: ");  
  Serial.println(my_value_2);         
}