#include <stdint.h>

#ifndef ATM328_UTIL_H
#define ATM328_UTIL_H

#define TOTAL_PINS 28
#define GROUP_B_PIN_COUNT 8
#define GROUP_C_PIN_COUNT 6
#define GROUP_D_PIN_COUNT 8

#define GROUP_B 1
#define GROUP_C 2
#define GROUP_D 3

#define OUTPUT 1
#define INPUT 2
#define HIGH 3
#define LOW 4

#define TRUE 1
#define FALSE 0

#define REG_PORTB *((volatile uint8_t*) 0x25)
#define REG_PORTC *((volatile uint8_t*) 0x28)
#define REG_PORTD *((volatile uint8_t*) 0x2B)
#define REG_DDRB  *((volatile uint8_t*) 0x24)
#define REG_DDRC  *((volatile uint8_t*) 0x27)
#define REG_DDRD  *((volatile uint8_t*) 0x2A)

#define BIT_PB0 (1 << 0)
#define BIT_PB1 (1 << 1)
#define BIT_PB2 (1 << 2)
#define BIT_PB3 (1 << 3)
#define BIT_PB4 (1 << 4)
#define BIT_PB5 (1 << 5)
#define BIT_PB6 (1 << 6)
#define BIT_PB7 (1 << 7)
#define BIT_PB8 (1 << 8)

#define BIT_PD0 (1 << 0)
#define BIT_PD1 (1 << 1)
#define BIT_PD2 (1 << 2)
#define BIT_PD3 (1 << 3)
#define BIT_PD4 (1 << 4)
#define BIT_PD5 (1 << 5)
#define BIT_PD6 (1 << 6)
#define BIT_PD7 (1 << 7)
#define BIT_PD8 (1 << 8)

#define BIT_PC0 (1 << 0)
#define BIT_PC1 (1 << 1)
#define BIT_PC2 (1 << 2)
#define BIT_PC3 (1 << 3)
#define BIT_PC4 (1 << 4)
#define BIT_PC5 (1 << 5)


#define TOGGLE(x, y)  ((x) ^= (1 << (y))) 
#define ENABLE(x, y)  ((x) |= (1 << (y))) 
#define DISABLE(x, y) ((x) &= (~(1 << (y))))

typedef struct {
  uint8_t group;
  uint8_t address;
  uint8_t pin;
} grouped_pin;

void setup_pins(void); 

void pin_set(uint8_t pin, uint8_t mode);
grouped_pin get_group_from_pin(uint8_t digit_pin);

#endif
