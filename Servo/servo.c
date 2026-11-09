#include "servo.h"
#include "io.h"
#include <stdbool.h>
#include <stdlib.h>

servo_pin servopins[MAX_SERVOS] = {0};
uint8_t servo_count = 0;
uint8_t current_servo = 0;
bool sort_enable = false;

ISR(TIMER1_COMPA_vect) {
  if (servo_count > 0) {
    // Set all active servo pins high to begin pulses.
    for (int i = 0; i < servo_count; i++) {
      pin_set(servopins[MAX_SERVOS - servo_count + i].pin, HIGH);
    }
    // Set interrupt B to start at the earliest interrupt time
    REG_OCR1BH = servopins[MAX_SERVOS - servo_count].pulse_width >> 8;
    REG_OCR1BL = servopins[MAX_SERVOS - servo_count].pulse_width & 0xFF;
  }
}

ISR(TIMER1_COMPB_vect) {

  if (servo_count > 0) {
    // Set reg B interrupt to occur on the earliest active servo pin.
    pin_set(servopins[current_servo].pin, LOW);
  }

  if (current_servo < MAX_SERVOS - 1) {
    current_servo++;
    REG_OCR1BH = servopins[current_servo].pulse_width >> 8;
    REG_OCR1BL = servopins[current_servo].pulse_width & 0xFF;
  } else {
    sort_servos();
    current_servo = MAX_SERVOS - servo_count;
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

  // Set the first OCR1B trigger to be the lowest of the existing servo pins.
  REG_OCR1BH = servopins[MAX_SERVOS - servo_count].pulse_width >> 8;
  REG_OCR1BL = servopins[MAX_SERVOS - servo_count].pulse_width & 0xFF;
  current_servo = MAX_SERVOS - servo_count;
  // Enable Timer1 compare match A and B interrupts
  REG_TIMSK1 |= BIT_OCIE1A;
  REG_TIMSK1 |= BIT_OCIE1B;

  // Enable global interrupts, officially starting the service
  REG_SREG |= BIT_INTERRUPT;
}

void set_servo_pin(uint8_t pin) {
  if (servo_count < MAX_SERVOS) {
    pin_set(pin, OUTPUT);
    servopins[MAX_SERVOS - ++servo_count] =
        (servo_pin){.pin = pin, .pulse_width = 650};
  }
}

void sort_servos(void) {
  if (sort_enable) {
    qsort(servopins, MAX_SERVOS, sizeof(servo_pin), compare_by_pulse);
    sort_enable = false;
  }
}

void change_servo_position(uint8_t pin, uint16_t degree) {
  for (int i = 1; i <= servo_count; i++) {
    if (servopins[MAX_SERVOS - i].pin == pin) {
      servopins[MAX_SERVOS - i].pulse_width = degree;
    }
  }
  sort_enable = true;
}

int compare_by_pulse(const void *a, const void *b) {
  const servo_pin *servo_A = (const servo_pin *)a;
  const servo_pin *servo_B = (const servo_pin *)b;

  return (servo_A->pulse_width - servo_B->pulse_width);
}
