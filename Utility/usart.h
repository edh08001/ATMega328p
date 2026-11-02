#include <stdint.h>
#include <stdbool.h>

#ifndef USART
#define USART

#define MAX_DIGITS 10

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
 * This value is calculated: (FOSC (hz) / 16 / BAUD - 1) and put into *
 * UBRR register                                                      *
 **********************************************************************/
void USART_Init(uint8_t ubrr); 

/**********************************************************************
 * USART_Transmit_Byte                                                *
 * Takes one uint8_t and transmits it. Checks to ensure that no other *
 * transmissions are pending, and the transmit buffer is ready to     *
 * receive more data.                                                 *
 **********************************************************************/
void USART_Transmit_Byte(uint8_t data); 

/**********************************************************************
 * USART_Transmit_String                                              *
 * Takes a character array and transmits it one                       *
 * by one until it comes across a null termiator (\0). Strings must   *
 * be null terminated, else the transmission behavior will overflow   *
 * the size of the array and the behavior will be undefined. Newline  *
 * if set true will transmit a carriage return and newline once the   *
 * string has been sent.                                              *
 **********************************************************************/
uint8_t USART_Transmit_String(char *string, bool newline);

/**********************************************************************
 * USART_Transmit_Number                                              *
 * Takes a number and converts it to a character array using modulus  *
 * and division, then sends it to USART_Transmit_String for final     *
 * transmission. Utilizes ASCII characters. If newline is set true    *
 * a carriage return and newline will be tranmitted at the end of the *
 * number.                                                            *
 **********************************************************************/
uint8_t USART_Transmit_Number(uint16_t number, bool newline);

#endif
