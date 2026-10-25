#include <stdint.h>
#ifndef TIME_H
#define TIME_H

//62499 = 1 second, 6250 = 0.1, etc, etc
#define TIME_SCALER 6250

#define REG_SREG   (*(volatile uint8_t  *)0x5F)
#define REG_TCCR1A (*(volatile uint8_t  *)0x80)
#define REG_TCCR1B (*(volatile uint8_t  *)0x81)
#define REG_TCNT1  (*(volatile uint16_t *)0x84)
#define REG_OCR1A  (*(volatile uint16_t *)0x88)
#define REG_TIMSK1 (*(volatile uint8_t  *)0x6F)
#define REG_TIFR1  (*(volatile uint8_t  *)0x36)

#define BIT_WGM12 (1 << 3)
#define BIT_CS12 (1 << 2)
#define BIT_OCIE1A (1 << 1)
#define BIT_OCF1A (1 << 1)
#define BIT_INTERRUPT (1 << 7)

extern void __vector_11(void) __attribute__((signal, used, externally_visible));
uint16_t get_time(); 
void start_time(void); 
void wait(uint32_t time);

#endif
