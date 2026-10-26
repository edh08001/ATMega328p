#include "atm328util.h"
#include "ssegled.h"
#include "time.h"

int main(int argc, char *argv[]) {

  uint32_t timer = 5;
  volatile uint8_t returner;
  setup_pins();
  start_time();

  // Digits 1, 2, 3, 4
  set_digit_pins(14, 13, 12, 11);

  // Segments G, C, Dec, D, E, B, F, A
  set_segment_pins(25, 24, 23, 19, 18, 17, 16, 15);

  while (1) {

    display_scrolling_number(1234);
  }
}
