#ifndef __COMMAND_H_
#define __COMMAND_H_

#include "config.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct command {
    uint8_t buffer[COMMAND_BUFFER_LENGTH];
    uint8_t index;
    bool execute_flag;
} command_t;

/* disabled for microcontroller
command_t *command_new(void);
 */

// returns pointer to the default command buffer
command_t *command_default(void);

bool command_is_full(command_t *cmd);

bool command_get_execution_flag(command_t *cmd);

void command_set_execution_flag(command_t *cmd, bool flag);

// returns true if b has been inserted
bool command_add(command_t *cmd, uint8_t b);

void command_reset(command_t *cmd);

// returns false if command not known
// clears execution flag
bool command_exec(command_t *cmd);

#endif
