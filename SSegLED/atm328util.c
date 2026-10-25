#include "atm328util.h"
#include <stdint.h>

const uint16_t PB_Pins[GROUP_B_PIN_COUNT] = {14, 15, 16, 17,
                                                  18, 19, 9,  10};
const unsigned char PC_Pins[GROUP_C_PIN_COUNT] = {23, 24, 25, 26, 27, 28};
const unsigned char PD_Pins[GROUP_D_PIN_COUNT] = {2, 3, 4, 5, 6, 11, 12, 13};
const unsigned char PX_Pins[GROUP_X_PIN_COUNT] = {1, 7, 8, 9, 10, 20, 21, 22};
grouped_pin grouped_pins[TOTAL_PINS + 1];
uint32_t timer = 0;

extern void __vector_11(void) {
  timer += 1; 
}

uint16_t get_time() {
  return timer;
}

void setup_pins(void) {
  for (int i = 1; i < TOTAL_PINS + 1; i++) {
    grouped_pins[i] = get_group_from_pin(i);
  }
}

void setup_timer(void) {
  // Sets the timer to run (clk/1024 prescaling)
  REG_TCCR1A = 0;
  REG_TCCR1B = 0;
  REG_TCNT1 = 0;

  // 2. Set CTC mode (WGM12 = 1)
  REG_TCCR1B |= BIT_WGM12;

  // 3. Set prescaler to 256 (CS12 = 1)
  REG_TCCR1B |= BIT_CS12;

  // 4. Set compare match value for 1 second (62499)
  REG_OCR1A = 625;

  // 5. Enable Timer1 compare match A interrupt via address 0x6F
  REG_TIMSK1 |= BIT_OCIE1A;

  ENABLE(SREG, INTERRUPT);
  
}
void delay(volatile long time) {
  while (time != 0) {
    time--;
  }
}

// Takes a pin (Actual #, TOP LEFT/RESET = 1 | TOP RIGHT/PC5 = 28) and sets data
// direction as out
unsigned char pin_set_output(unsigned char pin) {
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
unsigned char pin_set_input(unsigned char pin) {
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

unsigned char pin_set_high(unsigned char pin) {
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

unsigned char pin_set_low(unsigned char pin) {
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

unsigned char pin_toggle(unsigned char pin) {
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
grouped_pin get_group_from_pin(unsigned char digit_pin) {
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
