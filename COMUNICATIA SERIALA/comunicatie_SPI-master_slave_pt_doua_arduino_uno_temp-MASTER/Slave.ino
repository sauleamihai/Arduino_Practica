#define MISO 12
#define MOSI 11
#define PIN_CLOCK 13
#define CHIP_SELECT 10

float stepADC = 0.0048828125;

void setup_pins() {
  DDRB |= (1 << MOSI) | (1 << PIN_CLOCK) | (1 << CHIP_SELECT);
  DDRB &= ~(1 << MISO);
}

void start_transmission(int slave_pin) {
  PORTB &= ~(1 << (slave_pin - 8));
}

void stop_transmission(int slave_pin) {
  PORTB |= (1 << (slave_pin - 8));
}

void send_byte(byte dataByte) {
  for (int index_bits = 0; index_bits < 8; index_bits++) {
    bool current_bit = dataByte & (0x80 >> index_bits);
    digitalWrite(MOSI, current_bit);
    clock_cycle();
  }
}

void clock_cycle() {
  PORTB |= (1 << (PIN_CLOCK - 8));
  delayMicroseconds(10);
  PORTB &= ~(1 << (PIN_CLOCK - 8));
  delayMicroseconds(10);
}

void send_data_int(int data) {
  send_byte((byte)(data >> 8));
  send_byte((byte)(data & 0xFF));
}

void setup() {
  Serial.begin(9600);
  setup_pins();
}

unsigned int readTemperature() {
  unsigned int sensorRead = analogRead(A0);
  float voltageOut = sensorRead * stepADC;
  float temperature = (voltageOut - 0.5) * 100;
  return (unsigned int)temperature;
}

void communnicationSPI(int val1) {
  start_transmission(CHIP_SELECT);
  send_data_int(val1);
  stop_transmission(CHIP_SELECT);
  
  Serial.print("Send current temperature sent: ");
  Serial.print(val1);
  Serial.print("C");
}

void loop() {
  unsigned int temperature = readTemperature();
  communnicationSPI(temperature);
  delay(1000);
}
