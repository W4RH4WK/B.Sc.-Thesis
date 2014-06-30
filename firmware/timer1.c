#include "timer1.h"

#include <avr/io.h>
#include <stdint.h>

void timer1_init(void) {
    DDRD = (1<<4)|(1<<5);

    TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM13)|(1<<WGM12)|(1<<WGM11)|(1<<WGM10);
    TCCR1B = (1<<CS12);

    OCR1A = 1249;
    OCR1B = 998;
}

uint16_t timer1_get_ocr(void) {
    return OCR1B;
}

void timer1_set_ocr(uint16_t value) {
    OCR1B = value;
}
