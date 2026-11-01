#include "util.h" 

uint8_t get_specific_digit(uint8_t position, uint32_t number) {
  uint8_t digits = get_digit_count(number);
  for (int i = digits; i > position; i--) {
    number /= 10;
  }
  return (uint8_t)(number % 10);
}

uint8_t get_digit_count(uint32_t number) {
  uint8_t digits = 1;
  while (number / 10 != 0) {
    number /= 10;
    digits++;
  }
  return digits;
}
