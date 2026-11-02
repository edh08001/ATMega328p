#include <stdint.h>
#ifndef TIME_H
#define TIME_H

#define REG_SREG   (*(volatile uint8_t  *)0x5F)
#define REG_TCCR0A (*(volatile uint8_t  *)0x44)
#define REG_TCCR0B (*(volatile uint8_t  *)0x45)
#define REG_TCNT0  (*(volatile uint16_t *)0x46)
#define REG_OCR0A  (*(volatile uint16_t *)0x47)
#define REG_TIMSK0 (*(volatile uint8_t  *)0x6E)
#define REG_TIFR0  (*(volatile uint8_t  *)0x35)

#define BIT_WGM02 (1 << 3)
#define BIT_WGM01 (1 << 1)
#define BIT_WGM00 (1 << 0)
#define BIT_COM0A1 (1 << 7)
#define BIT_COM0A0 (1 << 6)
#define BIT_CS02 (1 << 2)
#define BIT_CS01 (1 << 1)
#define BIT_CS00 (1 << 0)
#define BIT_OCIE0A (1 << 1)
#define BIT_INTERRUPT (1 << 7)

extern void __vector_14(void) __attribute__((signal, used, externally_visible));
uint32_t get_time();
void start_time(void); 
void reset_time(void); 
void wait(uint32_t time) __attribute__((optimize("-O0")));

#endif
