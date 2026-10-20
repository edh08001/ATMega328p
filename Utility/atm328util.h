#ifndef ATM328_UTIL_H
#define ATM328_UTIL_H

#define TOGGLE(x, y) ((x) ^= (1 << (y))) 
#define ENABLE(x, y) ((x) |= (1 << (y))) 
#define DISABLE(x, y) ((x) &= (~(1 << (y))))

typedef struct {
  unsigned char group;
  unsigned char group_pin;
} grouped_pin;

void delay(volatile long time); 
unsigned char pin_set_output(unsigned char pin); 
unsigned char pin_bit_input(unsigned char pin); 
grouped_pin get_group_from_pin(unsigned char digit_pin);


#endif
