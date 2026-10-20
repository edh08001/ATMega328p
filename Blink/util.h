#ifndef _UTIL_H
#define _UTIL_H

#define TOGGLE(x, y) ((x) ^= (1 << (y))) 
#define ENABLE(x, y) ((x) |= (1 << (y))) 
#define DISABLE(x, y) ((x) &= (~(1 << (y))))

void delay(long time); 

#endif
