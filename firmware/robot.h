#ifndef __ROBOT_H_
#define __ROBOT_H_

#include "config.h"

#include <stdint.h>

#define ROBOT_COMMAND_GET_SENSOR        0x10
#define ROBOT_COMMAND_SET_LED           0x20
#define ROBOT_COMMAND_SET_VELOCITY      0x1a
#define ROBOT_COMMAND_DRIVE_REQUEST     0x1c
#define ROBOT_COMMAND_TURN_REQUEST      0x1d
#define ROBOT_COMMAND_ODOMETRY          0x1b
#define BAR_LEVEL_UP                    998
#define BAR_LEVEL_DOWN                  976
#define BAR_LEVEL_STEPS                 2

void robot_set_velocity(int8_t left, int8_t right);

void robot_set_led(uint8_t red, uint8_t blue);

void robot_drive_request(int8_t distance);

void robot_turn_request(int8_t angle);

void robot_get_odometry();

void robot_set_odometry(int8_t xlow, int8_t xheigh, int8_t ylow, int8_t
        yheigh, int8_t alphalow, int8_t alphaheigh);

void robot_get_sensor(void);

void robot_set_bar_level(uint8_t value);

void robot_raise_bar(void);

void robot_lower_bar(void);

/* IMPORTANT: this function trusts 'sendsize' ultimately, there is no check
 * against out of bound access.
 *
 * IMPORTANT: this function allocates readsize bytes on the stack, only use
 * small values to prevent a stack overflow.
 */
void robot_custom(uint8_t *senddata, uint8_t sendsize, uint8_t readsize);

#endif
