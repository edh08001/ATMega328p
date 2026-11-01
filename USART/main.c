#include <stdint.h>
#include "time.h"
#include "usart.h"

#define FOSC 16000000UL
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(int argc, char *argv[])
{
 
  start_time();
  USART_Init(MYUBRR);
  uint64_t num = 44294967295;

  while(1) {
    USART_Transmit_Number(num, false);
    USART_Transmit_String(" is my number!", true);
    wait(1000);
  }

}

