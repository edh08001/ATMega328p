#include "util.h"
#include "atm328pins.h"

int main(int argc, char *argv[]) {
  ENABLE(DDRB, PB5);

  while (1) {

    TOGGLE(PORTB, PB5);
    delay(1000000);

  }

}

