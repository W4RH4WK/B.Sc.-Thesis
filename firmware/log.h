#ifndef __LOG_H_
#define __LOG_H_

#include "config.h"

#include <avr/pgmspace.h>

#include "uart.h"

#ifdef LOG
    #define log(fmt, args...) fprintf_P(&uart_stream, PSTR(fmt LINE_ENDING), ##args)
#else
    #define log(fmt, args...)
#endif

#endif
