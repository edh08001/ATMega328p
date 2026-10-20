#include "atm328util.h"
#include "atm328pins.h"

const unsigned char PB_Pins[GROUP_B_PIN_COUNT] = {14, 15, 16, 17, 18, 19, 9, 10};
const unsigned char PC_Pins[GROUP_C_PIN_COUNT] = {23, 24, 25, 26, 27, 28};
const unsigned char PD_Pins[GROUP_D_PIN_COUNT] = {2, 3, 4, 5, 6, 11, 12, 13};
const unsigned char PX_Pins[GROUP_X_PIN_COUNT] = {1, 7, 8, 9, 10, 20, 21, 22};

void delay(volatile long time) {
  while (time != 0) {
    time--;
  }
}

//Takes a pin (Actual #, TOP LEFT/RESET = 1 | TOP RIGHT/PC5 = 28) and sets data direction as out 
unsigned char pin_set_output(unsigned char pin) {
  grouped_pin group = get_group_from_pin(pin);
  switch (group.group) {
    case GROUP_B: 
      ENABLE(DDRB, group.group_pin);
      break;
    case GROUP_C: 
      ENABLE(DDRC, group.group_pin);
      break;
    case GROUP_D: 
      ENABLE(DDRD, group.group_pin);
      break;
    default: 
      return 0;
  }
  return 1;
}

//Takes a pin (Actual #, TOP LEFT/RESET = 1 | TOP RIGHT/PC5 = 28) and sets data direction as in
unsigned char pin_set_input(unsigned char pin) {
  grouped_pin group = get_group_from_pin(pin);
  switch (group.group) {
    case GROUP_B: 
      DISABLE(DDRB, group.group_pin);
      break;
    case GROUP_C: 
      DISABLE(DDRC, group.group_pin);
      break;
    case GROUP_D: 
      DISABLE(DDRD, group.group_pin);
      break;
    default: 
      return 0;
  }
  return 1;
}

unsigned char pin_set_high(unsigned char pin) {
  grouped_pin group = get_group_from_pin(pin);
  switch (group.group) {
    case GROUP_B: 
      ENABLE(PORTB, group.group_pin);
      break;
    case GROUP_C: 
      ENABLE(PORTC, group.group_pin);
      break;
    case GROUP_D: 
      ENABLE(PORTD, group.group_pin);
      break;
    default: 
      return 0;
  }
  return 1;
}

unsigned char pin_set_low(unsigned char pin) {
  grouped_pin group = get_group_from_pin(pin);
  switch (group.group) {
    case GROUP_B: 
      DISABLE(PORTB, group.group_pin);
      break;
    case GROUP_C: 
      DISABLE(PORTC, group.group_pin);
      break;
    case GROUP_D: 
      DISABLE(PORTD, group.group_pin);
      break;
    default: 
      return 0;
  }
  return 1;
}

unsigned char pin_toggle(unsigned char pin) {
  grouped_pin group = get_group_from_pin(pin);
  switch (group.group) {
    case GROUP_B: 
      TOGGLE(PORTB, group.group_pin);
      break;
    case GROUP_C: 
      TOGGLE(PORTC, group.group_pin);
      break;
    case GROUP_D: 
      TOGGLE(PORTD, group.group_pin);
      break;
    default: 
      return 0;
  }
  return 1;
}

//Get the pin group (B, C, D, or X (Ancillary) and the group specific pin (i.e. PC5 returns GROUP_C and 5)
grouped_pin get_group_from_pin(unsigned char digit_pin) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < GROUP_B_PIN_COUNT; j++) {
      if (digit_pin == PB_Pins[j]) {
        return (grouped_pin){.group = GROUP_B, .group_pin = j};
      }
      if (digit_pin == PD_Pins[j]) {
        return (grouped_pin){.group = GROUP_D, .group_pin = j};
      }
      if (j < GROUP_C_PIN_COUNT && (digit_pin == PC_Pins[j])) {
        return (grouped_pin){.group = GROUP_C, .group_pin = j};
      }
    }
  }
  return (grouped_pin){.group = 0, .group_pin = 0};
}
