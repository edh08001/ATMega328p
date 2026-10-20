#include "util.h"

void delay(volatile long time) {
  while (time != 0) {
    time--;
  }
}
