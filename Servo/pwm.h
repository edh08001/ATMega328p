#include <avr/interrupt.h>

#ifndef SERVO_H
#define SERVO_H

#define MAX_SERVOS 8 

#define REG_SREG   (*(volatile uint8_t *)0x5F)
#define REG_TCCR1A (*(volatile uint8_t *)0x80)
#define REG_TCCR1B (*(volatile uint8_t *)0x81)
#define REG_TCNT1H (*(volatile uint8_t *)0x85)
#define REG_TCNT1L (*(volatile uint8_t *)0x84)
#define REG_OCR1AH (*(volatile uint8_t *)0x89)
#define REG_OCR1AL (*(volatile uint8_t *)0x88)
#define REG_OCR1BH (*(volatile uint8_t *)0x8B)
#define REG_OCR1BL (*(volatile uint8_t *)0x8A)
#define REG_TIMSK1 (*(volatile uint8_t *)0x6F)
#define REG_TIFR1  (*(volatile uint8_t *)0x36)

#define BIT_WGM12     (1 << 3)
#define BIT_CS12      (1 << 2)
#define BIT_CS11      (1 << 1)
#define BIT_CS10      (1 << 0)
#define BIT_OCIE1A    (1 << 1)
#define BIT_OCIE1B    (1 << 2)
#define BIT_OCF1A     (1 << 1)
#define BIT_INTERRUPT (1 << 7)

typedef struct {
  uint8_t pin;
  uint16_t pulse_width;
} servo_pin;

void start_servo_service(void); 
void change_servo_position(uint8_t pin, uint16_t degree); 
void sort_servos(void); 
void set_servo_pin(uint8_t pin); 

#endif
