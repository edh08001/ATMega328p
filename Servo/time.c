#include "time.h"

uint32_t time = 0;

extern void __vector_14(void) {
  time += 1; 
}

void start_time(void) {
  // Sets the timer to run (clk/1024 prescaling)
  REG_TCCR0A = 0;
  REG_TCCR0B = 0;
  REG_TCNT0 = 0;

  // Set CTC mode 
  REG_TCCR0A |= BIT_WGM01;

  // Set compare match value for 1/1000 of a second (250)
  REG_OCR0A = 249;

  // Set prescaler to 64 (CS00 | CS01)
  REG_TCCR0B |= BIT_CS01;
  REG_TCCR0B |= BIT_CS00;

  // Enable Timer1 compare match A interrupt via address 0x6F
  REG_TIMSK0 |= BIT_OCIE0A;

  REG_SREG |= BIT_INTERRUPT;
  
}

uint32_t get_time(void) {
  return time;
}

void reset_time(void) {
  time = 0;
}

void wait(volatile uint32_t wait_time) {
  uint32_t end_time = 0;
  uint8_t timer_started = 0;
  if (!timer_started) {
    end_time = get_time() + wait_time;
    timer_started = 1;
  }

  while (timer_started == 1) {
    if (end_time - get_time() == 0) {
      timer_started = 0;
    } else {
    }
  }
}
