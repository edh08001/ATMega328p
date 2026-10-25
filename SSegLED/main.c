#include "atm328util.h"
#include "ssegled.h"
#include "time.h"

int main(int argc, char *argv[]) {

  // Digits 1, 2, 3, 4
  setup_pins();
  start_time();

  set_digit_pins(14, 13, 12, 11);

  // Segments G, C, Dec, D, E, B, F, A
  set_segment_pins(25, 24, 23, 19, 18, 17, 16, 15);

  while (1) {

    /*
    if (REG_TIFR1 & BIT_OCF1A){
      flags++;
      REG_TIFR1 = BIT_OCF1A;
    }
    */
    display_multi_number(get_time());
    /*
    for (int j = 0; j < 10; j++) {
      for (volatile long k = 0; k < 10000; k++) {
        display_single_number(4, j);
      }
    }
    */
  }
}
