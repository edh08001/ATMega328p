#include "util.h"

#ifndef _ATM328P_PINS_H 
#define _ATM328P_PINS_H

#define PORTB *((volatile unsigned char*)0x25)
#define PORTC *((volatile unsigned char*)0x28)
#define PORTD *((volatile unsigned char*)0x2B)
#define DDRB *((volatile unsigned char*)0x24)
#define DDRC *((volatile unsigned char*)0x27)
#define DDRD *((volatile unsigned char*)0x2A)

#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7

#define PC0 0
#define PC1 1 
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5
#define PC6 6

#define PD0 0
#define PD1 1 
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

#endif

