#include <stdint.h>

#ifndef USART
#define USART

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

/**********************************************************************
 * USART_Init                                                         *
 * Initializes the USART capabilities of the microcontroller. Takes a *
 * uint8_t which is the scale factor as defined in the manual.        *
 * This value is calculated:   (clkspeed (hz) / 16 / baud rate - 1)   *
 **********************************************************************/
void USART_Init(uint8_t ubrr); 
void USART_Transmit(uint8_t data); 

/**********************************************************************
 * USART_Transmit_String                                              *
 * Takes a character array and transmits it one                       *
 * by one until it comes across a null termiator (\0). Strings must   *
 * be null terminated, else the transmission behavior will overflow   *
 * the size of the array and the behavior will be undefined.          *
 **********************************************************************/
uint8_t USART_Transmit_String(char *string);

#endif
