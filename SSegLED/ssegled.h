#include "atm328pins.h"

#ifndef _SSEGLED_H
#define _SSEGLED_H

#define DIGIT_PIN_COUNT 4
#define SEGMENT_PIN_COUNT 8

typedef enum {
  DIG_1 = 12,
  DIG_2 = 9,
  DIG_3 = 8,
  DIG_4 = 6,
} digit;

typedef enum {
  A = 11,
  F = 10,
  B = 7,
  E = 1,
  D = 2,
  C = 4,
  G = 5,
  DEC = 3
} segment;


typedef struct {
  segment segment;
  unsigned char port;
  unsigned char pin;
} segment_location;

typedef struct {
  digit digit;
  unsigned char pin;
} digit_location;

#endif

