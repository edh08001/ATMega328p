#include "pwm.h"
#include "time.h"

int main(int argc, char *argv[])
{

  start_time();
  set_servo_pin(15);
  set_servo_pin(17);
  start_servo_service();

  while(1) {
    for (int i = 175; i < 600; i+= 3){
      change_servo_position(15, 800-i);
      change_servo_position(17, i);
      wait(15);
    }
    for (int i = 600; i > 175; i-= 3){
      change_servo_position(15, 800-i);
      change_servo_position(17, i);
      wait(15);
    }
  }

}

