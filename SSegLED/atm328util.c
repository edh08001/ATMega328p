#include "atm328util.h"
#include <stdint.h>

const uint8_t PB_Pins[GROUP_B_PIN_COUNT] = {14, 15, 16, 17, 18, 19, 9, 10};
const uint8_t PC_Pins[GROUP_C_PIN_COUNT] = {23, 24, 25, 26, 27, 28};
const uint8_t PD_Pins[GROUP_D_PIN_COUNT] = {2, 3, 4, 5, 6, 11, 12, 13};
const uint8_t PX_Pins[GROUP_X_PIN_COUNT] = {1, 7, 8, 9, 10, 20, 21, 22};

grouped_pin grouped_pins[TOTAL_PINS + 1];

void setup_pins(void) {
  for (int i = 1; i < TOTAL_PINS + 1; i++) {
    grouped_pins[i] = get_group_from_pin(i);
  }
}

void delay(volatile long time) {
  while (time != 0) {
    time--;
  }
}

// Takes a pin (Actual #, TOP LEFT/RESET = 1 | TOP RIGHT/PC5 = 28) and sets data
// direction as out
uint8_t pin_set_output(uint8_t pin) {
  grouped_pin group = grouped_pins[pin];
  switch (group.group) {
  case GROUP_B:
    ENABLE(DDRB, group.pin);
    break;
  case GROUP_C:
    ENABLE(DDRC, group.pin);
    break;
  case GROUP_D:
    ENABLE(DDRD, group.pin);
    break;
  default:
    return 0;
  }
  return 1;
}

// Takes a pin (Actual #, TOP LEFT/RESET = 1 | TOP RIGHT/PC5 = 28) and sets data
// direction as in
uint8_t pin_set_input(uint8_t pin) {
  // grouped_pin group = get_group_from_pin(pin);
  grouped_pin group = grouped_pins[pin];
  switch (group.group) {
  case GROUP_B:
    DISABLE(DDRB, group.pin);
    break;
  case GROUP_C:
    DISABLE(DDRC, group.pin);
    break;
  case GROUP_D:
    DISABLE(DDRD, group.pin);
    break;
  default:
    return 0;
  }
  return 1;
}

uint8_t pin_set_high(uint8_t pin) {
  // grouped_pin group = get_group_from_pin(pin);
  grouped_pin group = grouped_pins[pin];
  switch (group.group) {
  case GROUP_B:
    ENABLE(PORTB, group.pin);
    break;
  case GROUP_C:
    ENABLE(PORTC, group.pin);
    break;
  case GROUP_D:
    ENABLE(PORTD, group.pin);
    break;
  default:
    return 0;
  }
  return 1;
}

uint8_t pin_set_low(uint8_t pin) {
  grouped_pin group = grouped_pins[pin];
  switch (group.group) {
  case GROUP_B:
    DISABLE(PORTB, group.pin);
    break;
  case GROUP_C:
    DISABLE(PORTC, group.pin);
    break;
  case GROUP_D:
    DISABLE(PORTD, group.pin);
    break;
  default:
    return 0;
  }
  return 1;
}

uint8_t pin_toggle(uint8_t pin) {
  grouped_pin group = grouped_pins[pin];
  switch (group.group) {
  case GROUP_B:
    TOGGLE(PORTB, group.pin);
    break;
  case GROUP_C:
    TOGGLE(PORTC, group.pin);
    break;
  case GROUP_D:
    TOGGLE(PORTD, group.pin);
    break;
  default:
    return 0;
  }
  return 1;
}

// Get the pin group (B, C, D, or X (Ancillary) and the group specific pin (i.e.
// PC5 returns GROUP_C and 5)
grouped_pin get_group_from_pin(uint8_t digit_pin) {
  for (int j = 0; j < GROUP_B_PIN_COUNT; j++) {
    if (digit_pin == PB_Pins[j]) {
      return (grouped_pin){.group = GROUP_B, .pin = j};
    }
    if (digit_pin == PD_Pins[j]) {
      return (grouped_pin){.group = GROUP_D, .pin = j};
    }
    if (j < GROUP_C_PIN_COUNT && (digit_pin == PC_Pins[j])) {
      return (grouped_pin){.group = GROUP_C, .pin = j};
    }
  }
  return (grouped_pin){.group = 0, .pin = 0};
}
