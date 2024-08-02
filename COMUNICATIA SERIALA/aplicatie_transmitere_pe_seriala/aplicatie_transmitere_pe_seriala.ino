#define F_CPU 16000000UL  // Assuming a 16 MHz clock speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define NumarBytes 2

int i=1;

//functie de initializare USART 
void USART_Init(unsigned int ubrr) {
    // Set the baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);  // Set high byte of UBRR
    UBRR0L = (unsigned char)ubrr;         // Set low byte of UBRR
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Set frame format: 8 data bits, 2 stop bits
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

//functie pentru a transmite un byte de date
void USART_Transmit(unsigned char data) {
    // asteptam ca bufferul de transmotere sa fie gol
    while (!(UCSR0A & (1 << UDRE0)));
    //data in bufffer
    UDR0 = data;
}


unsigned char USART_Receive(void) {
    // asteptam ca data sa fie primita 
    while (!(UCSR0A & (1 << RXC0)));
    // returnam datele de la buffer 
    return UDR0;
}

// trimitere de mesaj 
void SendString(char *StringPtr) {
    while (*StringPtr != 0x00) {
        USART_Transmit(*StringPtr);
        StringPtr++;
    }
}


void setup() {
    USART_Init(MYUBRR);
}

// Arduino loop function
void loop() {
    SendString("Laborator SMC\n");
    delay(1000); 
}

void myPWMCommand(){
 while (1)
{   
    if (UCSR0A & (1<<RXC0)) //If Usart control and status register A and Receive complete flag are true (Comparing the register with the value of RXC, which is a bit in the register)
    {
        my_data[i] = UDR0; //Read Usart Data Register, which is 1 byte
        i++; //Like Joachim Pileborg said, this should be in the if statement
    }

    if (i == NumarBytes)
    {
        /*my next code here and once thats done, its again in uart receive mode*/
        //Do something with the data
        i = 0;
    }
}
}
