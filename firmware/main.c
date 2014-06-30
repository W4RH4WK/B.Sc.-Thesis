#include "config.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdbool.h>

#include "command.h"
#include "log.h"
#include "timer1.h"
#include "twi.h"
#include "uart.h"

int main(void) {
    uart_init();
    twi_init();
    timer1_init();

    command_t *cmd = command_default();

    if(gBit(MCUCSR, 3)) {
        log("watchdog reset");
    }

    wdt_enable(WDTO_2S);

    log("init done");

    sei();

    while (true) {
        wdt_reset();

        // execute command
        if (command_get_execution_flag(cmd)) {
            cli();
            if (!command_exec(cmd)) {
                log("command not found");
            }
            command_reset(cmd);
            sei();
        }
    }

    return 0;
}
