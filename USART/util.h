#include <stdint.h>

#ifndef UTIL
#define UTIL 

#define DIGIT_TO_ASCII(x) ((x)+48)

/**********************************************************************
 * get_specific_digit                                                 *
 * Takes a position (starting at 1) and returns that position within  *
 * the supplied number.                                               *
 **********************************************************************/
uint8_t get_specific_digit(uint8_t position, uint32_t number); 

/**********************************************************************
 * get_digit_count                                                    *
 * Takes a 32 bit number and returns the number of digits contained.  *
 **********************************************************************/
uint8_t get_digit_count(uint32_t number); 

#endif
