#include <stdint.h>
#include "time.h"

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

void USART_Init(uint8_t ubrr) {
  /*Set baud rate*/
  REG_UBRR0H = (uint8_t)(ubrr>>8);
  REG_UBRR0L = (uint8_t)(ubrr);
  /*Enable receiver and transmitter*/
  REG_UCSR0B = (1<<TXEN0) | (1 << RXEN0);
  /*Set frame format: 8 data, 1 stop bit */
  REG_UCSR0C = (1 << UCSZ01) | (1<<UCSZ00);
}

void USART_Transmit(uint8_t data) {
  /*Wait for empty transmit buffer */
  while (!(REG_UCSR0A & (1<<UDRE0))); 

  uint8_t lo = (data << 4);
  uint8_t hi = (data >> 4);
  uint8_t swap = lo | hi;
  REG_UDR0 = data;
}

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

