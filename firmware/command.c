#include "command.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "robot.h"
#include "twi.h"

static command_t default_cmd;

/*
command_t *command_new(void) {
    command_t *cmd = (command_t *) malloc(sizeof(command_t));
    command_reset(cmd);
    return cmd;
}
 */

command_t *command_default(void) {
    return &default_cmd;
}

bool command_is_full(command_t *cmd) {
    return !(cmd->index < COMMAND_BUFFER_LENGTH);
}

bool command_add(command_t *cmd, uint8_t b) {
    if (command_is_full(cmd)) {
        return false;
    }

    cmd->buffer[cmd->index] = b;
    cmd->index++;
    return true;
}

bool command_get_execution_flag(command_t *cmd) {
    return cmd->execute_flag;
}

void command_set_execution_flag(command_t *cmd, bool flag) {
    cmd->execute_flag = flag;
}

void command_reset(command_t *cmd) {
    memset(cmd->buffer, 0, COMMAND_BUFFER_LENGTH);
    cmd->index = 0;
    cmd->execute_flag = false;
}

bool command_exec(command_t *cmd) {
    switch (cmd->buffer[0]) {
        case 'w':
            robot_set_velocity(30, 30);
            break;

        case 'a':
            robot_set_velocity(0, 30);
            break;

        case 's':
            robot_set_velocity(0, 0);
            break;

        case 'd':
            robot_set_velocity(30, 0);
            break;

        case 'q':
            robot_get_sensor();
            break;

        case 'r':
            robot_set_led(254, 254);
            break;

        case 'e':
            robot_set_led(0, 0);
            break;

        case 'x':
            robot_set_velocity(-15, -15);
            break;

        case 'u':
            robot_set_led(cmd->buffer[1], cmd->buffer[2]);
            break;

        case 'i':
            robot_set_velocity(cmd->buffer[1], cmd->buffer[2]);
            break;

        case 'o':
            robot_set_bar_level(cmd->buffer[1]);
            break;

        case 'h':
            robot_get_odometry();
            break;

        case 'j':
            robot_set_odometry(cmd->buffer[1], cmd->buffer[2], cmd->buffer[3],
                    cmd->buffer[4], cmd->buffer[5], cmd->buffer[6]);
            break;

        case 'k':
            robot_drive_request(cmd->buffer[1]);
            break;

        case 'l':
            robot_turn_request(cmd->buffer[1]);
            break;

        case '+':
            robot_raise_bar();
            break;

        case '-':
            robot_lower_bar();
            break;

        case 'm':
            {
                uint8_t sendsize = cmd->buffer[1];
                uint8_t readsize = cmd->buffer[2];
                uint8_t *data = cmd->buffer + 3;

                // prevent out of bound
                uint8_t sendsizemax = COMMAND_BUFFER_LENGTH - 3;
                if (sendsize > sendsizemax) {
                    sendsize = sendsizemax;
                }

                robot_custom(data, sendsize, readsize);
                break;
            }

        default:
            log("unknown command");
    }
    command_set_execution_flag(cmd, false);
    return true;
}
