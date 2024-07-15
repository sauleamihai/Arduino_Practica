const int data_pin = 7;
const int latch_pin = 6;
const int clock_pin = 5;

void setup()
{
  DDRD |= (1 << data_pin) | (1 << latch_pin) | (1 << clock_pin);
}

void loop()
{
  for (int i = 0; i < 256; i++)
  {
    PORTD &= ~(1 << latch_pin);
    shiftOut(data_pin, clock_pin, MSBFIRST, i);
    PORTD |= (1 << latch_pin);
    delay(1000);
  }
}
