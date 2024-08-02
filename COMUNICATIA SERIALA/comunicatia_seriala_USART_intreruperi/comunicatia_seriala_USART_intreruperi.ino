#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>  // Include Arduino core library

#define BAUD_PRESCALAR 0x0067  
volatile int i = 0;  
volatile uint8_t buffer[20];  
volatile uint8_t StrRxFlag = 0;  

void setup() {
 
  USART_interrupt_init();
  
 
  Serial.begin(9600);
}

void loop() {
  
  if (StrRxFlag) {
    
    Serial.println((char*)buffer);
    
    
    StrRxFlag = 0;
  }
}

void USART_interrupt_init(void) {
  
  cli();
  
  
  UBRR0 = BAUD_PRESCALAR;
  
  
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  
  // Set frame format: 8 data bits, 1 stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  
  // Enable global interrupts
  sei();
}

// ISR for USART RX complete interrupt
ISR(USART0_RX_vect) {
  // Read received character into buffer
  buffer[i] = UDR0;
  
  // Check for carriage return (end of string)
  if (buffer[i] == '\r' || buffer[i] == '\n') {
    // Set flag to indicate string reception
    StrRxFlag = 1;
    
    // Null-terminate the string
    buffer[i] = 0x00;
    
    // Reset buffer index
    i = 0;
  } else {
    // Increment buffer index if not end of string
    i++;
    
    // Prevent buffer overflow
    if (i >= sizeof(buffer)) {
      i = sizeof(buffer) - 1;
    }
  }
}
