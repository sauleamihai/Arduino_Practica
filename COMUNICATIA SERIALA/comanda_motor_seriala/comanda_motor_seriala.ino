#include <avr/io.h>
#include <avr/interrupt.h>

#define baud 9600
#define MYUBRR F_CPU/16/baud-1
#define InputPin1 1
#define InputPin2 2
#define Enable1And2 3

void setup();
void loop();
void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void SendString(char *StringPtr);
void HandlePWMCommand();
unsigned int pwm_value=0;

void setup() {
    DDRD |= (1 << InputPin1) | (1 << InputPin2);
    PORTD |= (1 << InputPin1);
    PORTD &= ~(1 << InputPin2);

    TCCR1B &= ~(1 << WGM13);
    TCCR1B |= (1 << WGM12);
    TCCR1A |= (1 << WGM10) | (1 << WGM11);
    TCCR1A |= (1 << COM1A1);
    TCCR1A &= ~(1 << COM1A0);
    TCCR1B |= (1 << CS10) | (1 << CS11);
    TCCR1B &= ~(1 << CS12);
    Serial.begin(9600);
    DDRB |= (1 << DDB1);
    OCR1A = 0;

    USART_Init(MYUBRR);
}

void loop() {
    HandlePWMCommand();
}

void USART_Init(unsigned int ubrr) {
   
    UBRR0H = (unsigned char)(ubrr >> 8);  
    UBRR0L = (unsigned char)ubrr;         
    
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

// Function to transmit a byte of data
void USART_Transmit(unsigned char data) {
   
    while (!(UCSR0A & (1 << UDRE0)));
    
    UDR0 = data;
}

unsigned char USART_Receive(void) {
    
    while (!(UCSR0A & (1 << RXC0)));
    
    return UDR0;
}

void SendString(char *StringPtr) {
    while (*StringPtr != 0x00) {
        USART_Transmit(*StringPtr);
        StringPtr++;
    }
}

void resetPwmVal(void){
  pwm_value=0;
}

void HandlePWMCommand() {
    resetPwmVal();
    unsigned char pwm_high = USART_Receive();
    unsigned char pwm_low = USART_Receive();
   
    Serial.println(pwm_high);
    Serial.println(pwm_low);
    unsigned int pwm_value = pwm_value | (pwm_high << 8) | pwm_low;
    Serial.println(pwm_value);
    
    OCR1A = pwm_value;
    
    SendString("PWM command received and set successfully.\r\n");
}
