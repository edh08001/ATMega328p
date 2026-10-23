#include "ssegled.h"
#include "atm328util.h"

//    AAA
//   F   B
//   F   B
//    GGG
//   E   C
//   E   C
//    DDD Dec

// Segments G, C, Dec, D, E, B, F, A
unsigned char numbers[10] = {0b01011111, 0b01000100, 0b10011101, 0b11010101,
                             0b11000110, 0b11010011, 0b11011011, 0b01000101,
                             0b11011111, 0b11000111};

// Digits 1, 2, 3, 4
unsigned char digit_pins[DIGIT_PIN_COUNT] = {14, 13, 12, 11};

// Segments G, C, Dec, D, E, B, F, A
unsigned char segment_pins[SEGMENT_PIN_COUNT] = {25, 24, 23, 19,
                                                 18, 17, 16, 15};
int display_single_number(unsigned char digit, unsigned char number) {
  for (int i = 0; i < DIGIT_PIN_COUNT; i++) {
    pin_set_high(digit_pins[i]);
  }

  // Turn on all digit 1 pins.
  pin_set_low(digit_pins[digit - 1]);
  for (int i = 0; i < SEGMENT_PIN_COUNT; i++) {
    if (numbers[number] & (1u << (7 - i))) {
      pin_set_high(segment_pins[i]);
    }
  }

  delay(20);
  // Turn off all digit 1 pins.
  pin_set_high(digit_pins[digit]);
  for (int i = 0; i < SEGMENT_PIN_COUNT; i++) {
    pin_set_low(segment_pins[i]);
  }
  return 1;
}

int display_multi_number(int number) {
  unsigned char digits = get_digit_count(number); 
  if (digits > 4) {
    display_single_number(2, 0);
    return 0;
  }
  for (int i = 4; i > (4 - digits); i--) {
    display_single_number(i, number % 10);
    number /= 10; 
  }
  return 1;
}

unsigned char get_digit_count(int number) {
  unsigned char digits = 1;
  while (number / 10 != 0) {
    number /= 10;
    digits++;
  }
  return digits;
}


int set_digit_pins(unsigned char digit_pin_1, unsigned char digit_pin_2,
                   unsigned char digit_pin_3, unsigned char digit_pin_4) {
  digit_pins[0] = digit_pin_1;
  pin_set_output(digit_pin_1);
  digit_pins[1] = digit_pin_2;
  pin_set_output(digit_pin_2);
  digit_pins[2] = digit_pin_3;
  pin_set_output(digit_pin_3);
  digit_pins[3] = digit_pin_4;
  pin_set_output(digit_pin_4);
  return 1;
}

//segments G, C, Dec, D, E, B, F, A. Must use high to low value pins
int set_segment_pins(unsigned char segment_pin_1, unsigned char segment_pin_2,
                     unsigned char segment_pin_3, unsigned char segment_pin_4,
                     unsigned char segment_pin_5, unsigned char segment_pin_6,
                     unsigned char segment_pin_7, unsigned char segment_pin_8) {
  segment_pins[0] = segment_pin_1;
  pin_set_output(segment_pin_1);
  segment_pins[1] = segment_pin_2;
  pin_set_output(segment_pin_2);
  segment_pins[2] = segment_pin_3;
  pin_set_output(segment_pin_3);
  segment_pins[3] = segment_pin_4;
  pin_set_output(segment_pin_4);
  segment_pins[4] = segment_pin_5;
  pin_set_output(segment_pin_5);
  segment_pins[5] = segment_pin_6;
  pin_set_output(segment_pin_6);
  segment_pins[6] = segment_pin_7;
  pin_set_output(segment_pin_7);
  segment_pins[7] = segment_pin_8;
  pin_set_output(segment_pin_8);
  return 1;
}

int set_outputs() {

  // Set Segments as Output
  for (int i = 0; i < SEGMENT_PIN_COUNT; i++) {
    pin_set_output(segment_pins[i]);
  }

  return 1;
}
