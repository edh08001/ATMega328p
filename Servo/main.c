#include "servo.h"
#include "time.h"

int main(int argc, char *argv[])
{

  uint8_t lowbyte, highbyte;
  uint16_t temp;
  start_time();
  set_servo_pin(15);
  set_servo_pin(16);
  start_servo_service();

  while(1) {
    for (int i = 150; i < 650; i+= 1){
      change_servo_position(15, i);
      change_servo_position(16, 800-i);
      wait(5);
    }
    for (int i = 650; i > 150; i-= 1){
      change_servo_position(15, i);
      change_servo_position(16, 800-i);
      wait(5);
    }
  }

}

