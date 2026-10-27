#include "atm328util.h"
#include <stdint.h>

grouped_pin grouped_pins[TOTAL_PINS + 1] = {{.group = 0, .bit = 0},
                                            {.group = GROUP_C, .bit = PC6},
                                            {.group = GROUP_D, .bit = PD0},
                                            {.group = GROUP_D, .bit = PD1},
                                            {.group = GROUP_D, .bit = PD2},
                                            {.group = GROUP_D, .bit = PD3},
                                            {.group = GROUP_D, .bit = PD4},
                                            {.group = 0, .bit = 0},
                                            {.group = 0, .bit = 0},
                                            {.group = GROUP_B, .bit = PB6},
                                            {.group = GROUP_B, .bit = PB7},
                                            {.group = GROUP_D, .bit = PD5},
                                            {.group = GROUP_D, .bit = PD6},
                                            {.group = GROUP_D, .bit = PD7},
                                            {.group = GROUP_B, .bit = PB0},
                                            {.group = GROUP_B, .bit = PB1},
                                            {.group = GROUP_B, .bit = PB2},
                                            {.group = GROUP_B, .bit = PB3},
                                            {.group = GROUP_B, .bit = PB4},
                                            {.group = GROUP_B, .bit = PB5},
                                            {.group = 0, .bit = 0},
                                            {.group = 0, .bit = 0},
                                            {.group = 0, .bit = 0},
                                            {.group = GROUP_C, .bit = PC0},
                                            {.group = GROUP_C, .bit = PC1},
                                            {.group = GROUP_C, .bit = PC2},
                                            {.group = GROUP_C, .bit = PC3},
                                            {.group = GROUP_C, .bit = PC4},
                                            {.group = GROUP_C, .bit = PC5}};

//Sets the pin based on the mode. Modes may be INPUT, OUTPUT, HIGH, LOW
void pin_set(uint8_t pin, uint8_t mode) {
  grouped_pin group = grouped_pins[pin];
  switch(group.group){
  case GROUP_B:
    switch(mode) {
    case OUTPUT:
      ENABLE(REG_DDRB, group.bit);
      break;
    case INPUT:
      DISABLE(REG_DDRB, group.bit);
      break;
    case HIGH:
      ENABLE(REG_PORTB, group.bit);
      break;
    case LOW:
      DISABLE(REG_PORTB, group.bit);
    default:
      break;
    }
    break;
  case GROUP_C:
    switch(mode) {
    case OUTPUT:
      ENABLE(REG_DDRC, group.bit);
      break;
    case INPUT:
      DISABLE(REG_DDRC, group.bit);
      break;
    case HIGH:
      ENABLE(REG_PORTC, group.bit);
      break;
    case LOW:
      DISABLE(REG_PORTC, group.bit);
    default:
      break;
    }
    break;
  case GROUP_D:
    switch(mode) {
    case OUTPUT:
      ENABLE(REG_DDRD, group.bit);
      break;
    case INPUT:
      DISABLE(REG_DDRD, group.bit);
      break;
    case HIGH:
      ENABLE(REG_PORTD, group.bit);
      break;
    case LOW:
      DISABLE(REG_PORTD, group.bit);
    default:
      break;
    }
    break;
  default:
    break;
  }
}
