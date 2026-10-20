#include "atm328util.h"

#ifndef _ATM328_PINS_H 
#define _ATM328_PINS_H

#define GROUP_B 1
#define GROUP_C 2
#define GROUP_D 3

#define TRUE 1
#define FALSE 0

#define REG_PORT_B 0x25
#define REG_PORT_C 0x28
#define REG_PORT_D 0x2B

#define REG_DDR_B 0x24
#define REG_DDR_C 0x27
#define REG_DDR_D 0x2A

#define PORTB *((volatile unsigned char*)(REG_PORT_B))
#define PORTC *((volatile unsigned char*)(REG_PORT_C))
#define PORTD *((volatile unsigned char*)(REG_PORT_D))
#define DDRB *((volatile unsigned char*)(REG_DDR_B))
#define DDRC *((volatile unsigned char*)(REG_DDR_C))
#define DDRD *((volatile unsigned char*)(REG_DDR_D))

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

extern const unsigned char PB_Pins[8]; 
extern const unsigned char PC_Pins[6]; 
extern const unsigned char PD_Pins[8]; 

#endif

