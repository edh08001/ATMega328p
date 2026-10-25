#include <stdint.h>

#ifndef ATM328_UTIL_H
#define ATM328_UTIL_H

#define TOTAL_PINS 28
#define GROUP_B_PIN_COUNT 8
#define GROUP_C_PIN_COUNT 6
#define GROUP_D_PIN_COUNT 8
#define GROUP_X_PIN_COUNT 8

#define GROUP_B 1
#define GROUP_C 2
#define GROUP_D 3
#define GROUP_X 4

#define TRUE 1
#define FALSE 0

#define REG_PORT_B 0x25
#define REG_PORT_C 0x28
#define REG_PORT_D 0x2B

#define REG_DDR_B 0x24
#define REG_DDR_C 0x27
#define REG_DDR_D 0x2A

//System Register
#define REG_SREG 0x5F

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

#define PORTB *((volatile unsigned char*)(REG_PORT_B))
#define PORTC *((volatile unsigned char*)(REG_PORT_C))
#define PORTD *((volatile unsigned char*)(REG_PORT_D))
#define DDRB *((volatile unsigned char*)(REG_DDR_B))
#define DDRC *((volatile unsigned char*)(REG_DDR_C))
#define DDRD *((volatile unsigned char*)(REG_DDR_D))
#define SREG *((volatile unsigned char*)(REG_SREG))
#define TCCR1A *((volatile unsigned char*)(REG_TCCR1A))
#define TCCR1B *((volatile unsigned char*)(REG_TCCR1B))
#define TIMSK1 *((volatile unsigned char*)(REG_TIMSK1))
#define TIFR1 *((volatile unsigned char*)(REG_TIFR1))
#define OCR1A *((volatile unsigned int*)(REG_OCR1A))

#define PB0 14
#define PB1 15
#define PB2 16
#define PB3 17
#define PB4 18
#define PB5 19
#define PB6 9
#define PB7 10

#define PC0 23
#define PC1 24
#define PC2 25
#define PC3 26
#define PC4 27
#define PC5 28

#define PD0 2
#define PD1 3
#define PD2 4
#define PD3 5
#define PD4 6
#define PD5 11
#define PD6 12
#define PD7 13

#define RESET 1
#define VCC_P 7
#define GND_P 8
#define CRYSTAL_1 9
#define CRYSTAL_2 10
#define AVCC 20
#define AREF 21
#define GND_S 22

//SREG Bits
#define INTERRUPT 7

#define TOGGLE(x, y) ((x) ^= (1 << (y))) 
#define ENABLE(x, y) ((x) |= (1 << (y))) 
#define DISABLE(x, y) ((x) &= (~(1 << (y))))

typedef struct {
  unsigned char group;
  unsigned char pin;
} grouped_pin;

void setup_pins(void); 

void delay(volatile long time); 
void setup_timer(void); 

unsigned char pin_set_output(unsigned char pin); 
unsigned char pin_set_input(unsigned char pin); 
unsigned char pin_set_high(unsigned char pin); 
unsigned char pin_set_low(unsigned char pin); 
unsigned char pin_toggle(unsigned char pin); 
grouped_pin get_group_from_pin(unsigned char digit_pin);

extern void __vector_11(void) __attribute__((signal, used, externally_visible));
uint16_t get_time(); 
#endif
