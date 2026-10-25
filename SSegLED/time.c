#include "time.h"

uint32_t time = 0;

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

  // 3. Set prescaler to 256 (CS12 = 1)
  REG_TCCR1B |= BIT_CS12;
  
  // 4. Set compare match value for 1 second (62499)
  REG_OCR1A = 62499;

  // 5. Enable Timer1 compare match A interrupt via address 0x6F
  REG_TIMSK1 |= BIT_OCIE1A;

  REG_SREG |= BIT_INTERRUPT;
  
}

uint16_t get_time(void) {
  return time;
}

void reset_time(void) {
  time = 0;
}

void wait(uint32_t time) {
  volatile uint32_t start_time = get_time();
  uint32_t end_time = start_time + time;
  while (get_time() <= end_time) {
    start_time++;
  }
}
