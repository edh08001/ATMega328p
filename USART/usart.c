#include "usart.h"
#include "util.h"

void USART_Init(uint8_t ubrr) {
  /*Set baud rate*/
  REG_UBRR0H = (uint8_t)(ubrr>>8);
  REG_UBRR0L = (uint8_t)(ubrr);
  /*Enable receiver and transmitter*/
  REG_UCSR0B = (1<<TXEN0) | (1 << RXEN0);
  /*Set frame format: 8 data, 1 stop bit */
  REG_UCSR0C = (1 << UCSZ01) | (1<<UCSZ00);
}

void USART_Transmit_Byte(uint8_t data) {
  /*Wait for empty transmit buffer */
  while (!(REG_UCSR0A & (1<<UDRE0))); 

  REG_UDR0 = data;
}

uint8_t USART_Transmit_String(char *string, bool newline) {
  char *arr = string;
  uint8_t tx_len = 0;
  while (*arr != '\0') {
    USART_Transmit_Byte(*arr);
    arr++;
    tx_len++;
  }
  if (newline) {
    USART_Transmit_Byte('\r');
    USART_Transmit_Byte('\n');
  }
  return tx_len;
}

uint8_t USART_Transmit_Number(uint16_t number, bool newline) {
  uint8_t digits = get_digit_count(number);
  uint8_t i = (digits - 1);
  char arr[MAX_DIGITS + 1];
  do {
    arr[i--] = DIGIT_TO_ASCII((number % 10));
    number /= 10;
  } while (number != 0);
  arr[digits] = '\0';
  
  return USART_Transmit_String(arr, newline);
}
