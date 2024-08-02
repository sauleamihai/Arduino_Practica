#define NumarBytes 2

int i = 0;
unsigned char my_data[NumarBytes];

// Initialize Serial Communication
void setup() {
    Serial.begin(9600); // Initialize serial with baud rate 9600
}

// Function to send a string
void SendString(const char *StringPtr) {
    while (*StringPtr != '\0') {
        Serial.write(*StringPtr);
        StringPtr++;
    }
}

// Function to receive and process data
void myPWMCommand() {
    while (Serial.available() > 0) { // Check if data is available to read
        my_data[i] = Serial.read(); // Read the data
        i++;
        if (i == NumarBytes) {
            // Process the data in my_data array
            // For example, echo the received data back
            for (unsigned char j = 0; j < NumarBytes; j++) {
                Serial.write(my_data[j]);
            }
            i = 0; // Reset index
        }
    }
}

void loop() {
    SendString("Laborator SMC\n");
    delay(1000); // Delay for 1 second

    myPWMCommand(); // Call the command function
}
