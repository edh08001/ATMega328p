#include <stdint.h>
#include "time.h"
#include "usart.h"

#define FOSC 16000000UL
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#define REG_UBRR0H *((volatile uint8_t*) 0xC5)
#define REG_UBRR0L *((volatile uint8_t*) 0xC4)
#define REG_UCSR0C *((volatile uint8_t*) 0xC2)
#define REG_UCSR0B *((volatile uint8_t*) 0xC1)
#define REG_UCSR0A *((volatile uint8_t*) 0xC0)
#define REG_UDR0   *((volatile uint8_t*) 0xC6)

#define RXEN0 4
#define TXEN0 3
#define USBS0 3
#define UCSZ00 1
#define UCSZ01 2
#define UDRE0 5

int main(int argc, char *argv[])
{
 
  start_time();
  USART_Init(MYUBRR);

  while(1) {
  
    USART_Transmit(0x4D);
    USART_Transmit(0x4F);
    USART_Transmit(0x4F);
    USART_Transmit('\r');
    USART_Transmit('\n');
    wait(1000);
    
  }

}

