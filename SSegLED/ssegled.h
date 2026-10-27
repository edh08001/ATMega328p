#include "atm328util.h"

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


void set_outputs(uint8_t arr[8], uint8_t len); 
void display_single_number(uint8_t digit, uint8_t number);
uint16_t display_multi_number(uint16_t number); 
uint8_t get_digit_count(uint32_t number); 
uint8_t display_scrolling_number(uint32_t number); 
uint8_t get_specific_digit(uint8_t position, uint32_t number); 
uint8_t set_digit_pins(uint8_t digit_pin_1, uint8_t digit_pin_2,
                       uint8_t digit_pin_3, uint8_t digit_pin_4); 
uint8_t set_segment_pins(uint8_t segment_pin_1, uint8_t segment_pin_2,
                         uint8_t segment_pin_3, uint8_t segment_pin_4,
                         uint8_t segment_pin_5, uint8_t segment_pin_6,
                         uint8_t segment_pin_7, uint8_t segment_pin_8); 
#endif

