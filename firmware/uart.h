#ifndef __UART_H_
#define __UART_H_

#include "config.h"

#include <avr/pgmspace.h>
#include <stdio.h>

#define uart_printf(fmt, args...)      fprintf_P(&uart_stream, PSTR(fmt LINE_ENDING), ##args)
#define uart_printf_nole(fmt, args...) fprintf_P(&uart_stream, PSTR(fmt), ##args)

extern FILE uart_stream;

void uart_init(void);

void uart_put_char(char c);

int uart_put_char_stream(char c, FILE* stream);

#endif
