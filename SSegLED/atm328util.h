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

#define PORTB *((volatile uint8_t*) 0x25)
#define PORTC *((volatile uint8_t*) 0x28)
#define PORTD *((volatile uint8_t*) 0x2B)
#define DDRB  *((volatile uint8_t*) 0x24)
#define DDRC  *((volatile uint8_t*) 0x27)
#define DDRD  *((volatile uint8_t*) 0x2A)

#define TOGGLE(x, y)  ((x) ^= (1 << (y))) 
#define ENABLE(x, y)  ((x) |= (1 << (y))) 
#define DISABLE(x, y) ((x) &= (~(1 << (y))))

typedef struct {
  uint8_t group;
  uint8_t pin;
} grouped_pin;

void setup_pins(void); 

void delay(volatile long time); 

uint8_t pin_set_output(uint8_t pin); 
uint8_t pin_set_input(uint8_t pin); 
uint8_t pin_set_high(uint8_t pin); 
uint8_t pin_set_low(uint8_t pin); 
uint8_t pin_toggle(uint8_t pin); 
grouped_pin get_group_from_pin(uint8_t digit_pin);

#endif
