#include "atm328pins.h"
#include "atm328util.h"
#include "ssegled.h"

int main(int argc, char *argv[]) {
  // Digits 1, 2, 3, 4
  unsigned char digit_pins[DIGIT_PIN_COUNT] = {14, 13, 12, 11};

  // Segments Dec, A, B, C, D, E, F, G
  unsigned char segment_pins[SEGMENT_PIN_COUNT] = {25, 24, 23, 19,
                                                   18, 17, 16, 15};

  // Set Digits as Output
  for (int i = 0; i < DIGIT_PIN_COUNT; i++) {
    pin_set_output(digit_pins[i]);
  }

  // Set Segments as Output
  for (int i = 0; i < SEGMENT_PIN_COUNT; i++) {
    pin_set_output(segment_pins[i]);
  }

  while (1) {
    // Reset digit pins. Cathode = enable is reset
    for (int i = 0; i < DIGIT_PIN_COUNT; i++) {
      pin_set_high(digit_pins[i]);
    }

    delay(20);
    // Turn on all digit 1 pins.
    pin_set_low(digit_pins[0]);
    for (int i = 0; i < SEGMENT_PIN_COUNT; i++) {
      pin_set_high(segment_pins[i]);
    }
    delay(20);
    // Turn off all digit 1 pins.
    pin_set_high(digit_pins[0]);
    for (int i = 0; i < SEGMENT_PIN_COUNT; i++) {
      pin_set_low(segment_pins[i]);
    }
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
