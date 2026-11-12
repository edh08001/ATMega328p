#include "io.h"
#include "pwm.h"
#include <stdbool.h>

servo_pin servopins[MAX_SERVOS] = {0};
uint8_t servo_count = 0;
uint8_t current_servo = 0;

ISR(TIMER1_COMPA_vect) {
  if (servo_count > 0 && servo_count < MAX_SERVOS) {
    // The cycle has finished.
    // Set the current servo to the first available in the array.
    current_servo = 0;

    // Set interrupt B to start at the first interrupt in the array
    REG_OCR1BH = servopins[current_servo].pulse_width >> 8;
    REG_OCR1BL = servopins[current_servo].pulse_width & 0xFF;

    // Set the corresponding pin to high
    pin_set(servopins[current_servo].pin, HIGH);
  }
}

ISR(TIMER1_COMPB_vect) {

  if (servo_count > 0 && servo_count < MAX_SERVOS) {
    //Pulse is finished. Set the current active pin low.
    pin_set(servopins[current_servo].pin, LOW);

    //Get the next servo 
    current_servo++;

    if (current_servo < servo_count) {
      //Set the pin high
      pin_set(servopins[current_servo].pin, HIGH);
      //Calculate the next interrupt based on the current timer and the next pulse width. 
      uint16_t next_timer = (uint16_t)((REG_TCNT1L & 0xFF) | (REG_TCNT1H << 8)) + servopins[current_servo].pulse_width + 4;
      //Set the interrupt equal to the new time
      REG_OCR1BH = next_timer >> 8;
      REG_OCR1BL = next_timer & 0xFF;
    }
  }
}

void start_servo_service(void) {
  // Reset timer control registers
  REG_TCCR1A = 0;
  REG_TCCR1B = 0;
  REG_TCNT1H = 0;
  REG_TCNT1L = 0;

  // 2. Set CTC mode (WGM12 = 1)
  REG_TCCR1B |= BIT_WGM12;

  // 3. Set prescaler to 64 (CS10 | CS11)
  REG_TCCR1B |= (BIT_CS11 | BIT_CS10);

  // 4. Set CTC TOP value to trigger at 20ms
  REG_OCR1AH = 5000 >> 8;
  REG_OCR1AL = 5000 & 0xFF;
  // This means the following values for OCR1B will be representative
  // of their respective pulse times.
  // 175         250            375           500         725
  // 0.5ms       1ms            1.5ms         2ms         2.5ms

  // Set the first OCR1B trigger to be the first of the set servo pins.
  REG_OCR1BH = servopins[0].pulse_width >> 8;
  REG_OCR1BL = servopins[0].pulse_width & 0xFF;

  // Enable Timer1 compare match A and B interrupts
  REG_TIMSK1 |= BIT_OCIE1A;
  REG_TIMSK1 |= BIT_OCIE1B;

  // Enable global interrupts, officially starting the service
  REG_SREG |= BIT_INTERRUPT;
}

void set_servo_pin(uint8_t pin) {
  if (servo_count < MAX_SERVOS) {
    pin_set(pin, OUTPUT);
    servopins[servo_count++] = (servo_pin){.pin = pin, .pulse_width = 375};
  }
}

void change_servo_position(uint8_t pin, uint16_t degree) {
  for (int i = 0; i < servo_count; i++) {
    if (servopins[i].pin == pin) {
      servopins[i].pulse_width = degree;
    }
  }
}
