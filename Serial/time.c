#include "time.h"

uint64_t time = 0;

extern void __vector_11(void) {
  time += 1; 
}

void start_time(void) {
  // Sets the timer to run (clk/1024 prescaling)
  REG_TCCR1A = 0;
  REG_TCCR1B = 0;
  REG_TCNT1 = 0;

  // 2. Set CTC mode (WGM12 = 1)
  REG_TCCR1B |= BIT_WGM12;

  // 3. Set prescaler to 64 (CS10 | CS11)
  REG_TCCR1B |= (BIT_CS11 | BIT_CS10);
  
  // 4. Set compare match value for 1/1000 of a second (250)
  REG_OCR1A = 250;

  // 5. Enable Timer1 compare match A interrupt via address 0x6F
  REG_TIMSK1 |= BIT_OCIE1A;

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
