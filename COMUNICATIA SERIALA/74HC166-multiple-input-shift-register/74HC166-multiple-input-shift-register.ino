int ioSelect = 2;
int clockPulse = 3;
int dataOut = 4;

int j;
int value;

byte switchVar = 0;

void setup() {
  DDRD |= (1 << ioSelect) | (1 << clockPulse); // Set ioSelect and clockPulse as output
  DDRD &= ~(1 << dataOut);                     // Set dataOut as input
  Serial.begin(9600);
}

void loop() {
  byte dataIn = 0;
  PORTD &= ~((1 << ioSelect) | (1 << clockPulse)); // Clear ioSelect and clockPulse
  PORTD |= (1 << clockPulse);                      // Set clockPulse
  PORTD |= (1 << ioSelect);                        // Set ioSelect
  
  for (j = 0; j < 8; j++) {
    value = digitalRead(dataOut);                  // Read dataOut
    Serial.print("Button position ");
    Serial.print(j);
    Serial.print(" Button Value: ");
    Serial.println(value);
    
    if (value) {
      dataIn |= (1 << j);                          // Set the corresponding bit in dataIn
    }
    
    PORTD &= ~(1 << clockPulse);                   // Clear clockPulse
    PORTD |= (1 << clockPulse);                    // Set clockPulse
  }
  
  if (switchVar != dataIn) {
    switchVar = dataIn;
    Serial.print("dataIn DEC: ");
    Serial.println(dataIn, DEC);
    Serial.print("dataIn BIN: ");
    Serial.println(dataIn, BIN);
  }
  
  delay(500); // Adjust the delay as needed
}
