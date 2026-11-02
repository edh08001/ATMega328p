#include "time.h"
#include "usart.h"

#define FOSC 16000000UL
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(int argc, char *argv[])
{
  USART_Init(MYUBRR);
  start_time();

  while(1) {
    USART_Transmit_String("Hi?", true);
    wait(1000);
    //USART_Transmit_String(" is my number!", true);
  }

}

