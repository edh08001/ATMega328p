#include "servo.h"

#define FOSC 16000000UL
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(int argc, char *argv[])
{

  uint8_t lowbyte, highbyte;
  uint16_t temp;

  set_servo_pin(15);
  start_servo_service();

  while(1) {
  }

}

