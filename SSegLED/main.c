#include "ssegled.h"
#include "atm328util.h"
#include "atm328pins.h"


int main(int argc, char *argv[])
{
  unsigned char digit_pins[4] = {14, 13, 12, 11};

  for (int i = 0; i < 4; i++) {
    pin_set_output(digit_pins[i]);
  }
  
  //ENABLE(DDRB, 0);
  //ENABLE(DDRD, 7);
  //ENABLE(DDRD, 6);
  //ENABLE(DDRD, 5);
  ENABLE(DDRB, 1);
  ENABLE(DDRB, 2);
  ENABLE(DDRB, 3);
  ENABLE(DDRB, 4);
  ENABLE(DDRB, 5);
  ENABLE(DDRC, 0);
  ENABLE(DDRC, 1);
  ENABLE(DDRC, 2);

  while (1) {
  ENABLE(PORTB, 0);
  ENABLE(PORTD, 7);
  ENABLE(PORTD, 6);
  ENABLE(PORTD, 5);


  DISABLE(PORTB, 0);
  ENABLE(PORTB, 1);
  ENABLE(PORTB, 2);
  delay(20);
  ENABLE(PORTB, 0);
  DISABLE(PORTB, 1);
  DISABLE(PORTB, 2);
  delay(20);
  DISABLE(PORTD, 7);
  ENABLE(PORTB, 3);
  ENABLE(PORTB, 4);
  delay(20);
  ENABLE(PORTD, 7);
  DISABLE(PORTB, 3);
  DISABLE(PORTB, 4);
  delay(20);

  
  }

}

