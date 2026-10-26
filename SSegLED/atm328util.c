#include "atm328util.h"
#include <stdint.h>

const uint8_t PB_Pins[GROUP_B_PIN_COUNT] = {14, 15, 16, 17, 18, 19, 9, 10};
const uint8_t PC_Pins[GROUP_C_PIN_COUNT] = {23, 24, 25, 26, 27, 28};
const uint8_t PD_Pins[GROUP_D_PIN_COUNT] = {2, 3, 4, 5, 6, 11, 12, 13};

grouped_pin grouped_pins[TOTAL_PINS + 1];

void setup_pins(void) {
  for (int i = 1; i < TOTAL_PINS + 1; i++) {
    grouped_pins[i] = get_group_from_pin(i);
  }
}

//Sets the pin based on the mode. Modes may be INPUT, OUTPUT, HIGH, LOW
void pin_set(uint8_t pin, uint8_t mode) {
  grouped_pin group = grouped_pins[pin];
  switch(group.group){
  case GROUP_B:
    switch(mode) {
    case OUTPUT:
      ENABLE(REG_DDRB, group.pin);
      break;
    case INPUT:
      DISABLE(REG_DDRB, group.pin);
      break;
    case HIGH:
      ENABLE(REG_PORTB, group.pin);
      break;
    case LOW:
      DISABLE(REG_PORTB, group.pin);
    default:
      break;
    }
    break;
  case GROUP_C:
    switch(mode) {
    case OUTPUT:
      ENABLE(REG_DDRC, group.pin);
      break;
    case INPUT:
      DISABLE(REG_DDRC, group.pin);
      break;
    case HIGH:
      ENABLE(REG_PORTC, group.pin);
      break;
    case LOW:
      DISABLE(REG_PORTC, group.pin);
    default:
      break;
    }
    break;
  case GROUP_D:
    switch(mode) {
    case OUTPUT:
      ENABLE(REG_DDRD, group.pin);
      break;
    case INPUT:
      DISABLE(REG_DDRD, group.pin);
      break;
    case HIGH:
      ENABLE(REG_PORTD, group.pin);
      break;
    case LOW:
      DISABLE(REG_PORTD, group.pin);
    default:
      break;
    }
    break;
  default:
    break;
  }
}

// Get the pin group (B, C, or D and the group specific pin (i.e.
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
