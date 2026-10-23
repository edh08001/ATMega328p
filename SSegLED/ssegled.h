#include "atm328pins.h"

#ifndef _SSEGLED_H
#define _SSEGLED_H

#define DIGIT_PIN_COUNT 4
#define SEGMENT_PIN_COUNT 8

  //    AAA
  //   F   B
  //   F   B
  //    GGG
  //   E   C
  //   E   C
  //    DDD Dec

  // Segments G, C, Dec, D, E, B, F, A


int set_outputs();
int display_single(unsigned char digit, unsigned char number);
int set_digit_pins(unsigned char digit_pin_1, unsigned char digit_pin_2,
                   unsigned char digit_pin_3, unsigned char digit_pin_4); 
int set_segment_pins(unsigned char segment_pin_1, unsigned char segment_pin_2,
                     unsigned char segment_pin_3, unsigned char segment_pin_4,
                     unsigned char segment_pin_5, unsigned char segment_pin_6,
                     unsigned char segment_pin_7, unsigned char segment_pin_8); 
#endif

