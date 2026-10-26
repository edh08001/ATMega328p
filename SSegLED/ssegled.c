#include "ssegled.h"
#include "atm328util.h"
#include "time.h"

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

void display_single_number(unsigned char digit, unsigned char number) {
  for (int i = 0; i < DIGIT_PIN_COUNT; i++) {
    pin_set(digit_pins[i], HIGH);
  }
  // Turn on all digit 1 pins.
  pin_set(digit_pins[digit - 1], LOW);
  for (int i = 0; i < SEGMENT_PIN_COUNT; i++) {
    if (numbers[number] & (1u << (7 - i))) {
      pin_set(segment_pins[i], HIGH);
    }
  }
  // Turn off all digit 1 pins.
  pin_set(digit_pins[digit], HIGH);
  for (int i = 0; i < SEGMENT_PIN_COUNT; i++) {
    pin_set(segment_pins[i], LOW);
  }
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

int display_scrolling_number(int number) {
  unsigned char digits = get_digit_count(number);
  unsigned char display_count = 0;
  //for (int i = 0; i < digits; i++) {
    while (display_count <= 4){
      uint64_t end_time = get_time() + 500;
      while (end_time > get_time()) {
        for (int j = 0; j < display_count; j++) {
          display_single_number(4-j, get_specific_digit(display_count-j, number));
        }
      }
      display_count++;
    }
  //}
  return 1;
}

int get_specific_digit(int position, int number) {
  unsigned char digits = get_digit_count(number);
  for (int i = digits; i > position; i--) {
     number /= 10;
  }
  return number % 10;
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
  digit_pins[1] = digit_pin_2;
  digit_pins[2] = digit_pin_3;
  digit_pins[3] = digit_pin_4;
  set_outputs(digit_pins, DIGIT_PIN_COUNT);
  return 1;
}

// segments G, C, Dec, D, E, B, F, A. Must use high to low value pins
int set_segment_pins(unsigned char segment_pin_1, unsigned char segment_pin_2,
                     unsigned char segment_pin_3, unsigned char segment_pin_4,
                     unsigned char segment_pin_5, unsigned char segment_pin_6,
                     unsigned char segment_pin_7, unsigned char segment_pin_8) {
  segment_pins[0] = segment_pin_1;
  segment_pins[1] = segment_pin_2;
  segment_pins[2] = segment_pin_3;
  segment_pins[3] = segment_pin_4;
  segment_pins[4] = segment_pin_5;
  segment_pins[5] = segment_pin_6;
  segment_pins[6] = segment_pin_7;
  segment_pins[7] = segment_pin_8;

  set_outputs(segment_pins, SEGMENT_PIN_COUNT);
  return 1;
}

void set_outputs(uint8_t arr[8], uint8_t len) {

  // Set Segments as Output
  for (int i = 0; i < len; i++) {
    pin_set(arr[i], OUTPUT);
  }

}
