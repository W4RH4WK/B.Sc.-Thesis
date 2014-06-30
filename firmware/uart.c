#include "uart.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "log.h"
#include "command.h"

FILE uart_stream = FDEV_SETUP_STREAM(uart_put_char_stream, NULL, _FDEV_SETUP_WRITE);

void uart_init(void) {
    // 9600 baud
    UBRRH = 0x00;
    UBRRL = 0x67;

    UCSRB = (1<<RXEN)|(1<<RXCIE)|(1<<TXEN);

    // setup stream
    stdout = &uart_stream;
    stdin = &uart_stream;
    stderr = &uart_stream;
}

void uart_put_char(char c) {
    while (!gBit(UCSRA, UDRE));
    UDR = c;
}

int uart_put_char_stream(char c, FILE* stream) {
    uart_put_char(c);
    return 0;
}

// add byte to command buffer
// flag command buffer for execution if \n is received
// ignore \r to prevent double execution
ISR(USART_RXC_vect) {
    char c = UDR;

    command_t *cmd = command_default();

    switch (c) {
        case '\r':
            break;

        case '\n':
            command_set_execution_flag(cmd, true);
            log("command execution marked");
            break;

        default:
            if (!command_add(cmd, c)) {
                log("command to long");
            }
    }
}
