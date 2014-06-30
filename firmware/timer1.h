#ifndef __TIMER1_H_
#define __TIMER1_H_

#include "config.h"

#include <stdint.h>


void timer1_init(void);

uint16_t timer1_get_ocr(void);

void timer1_set_ocr(uint16_t value);

#endif
