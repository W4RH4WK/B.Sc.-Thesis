#include "robot.h"
#include <util/twi.h>

#include "log.h"
#include "timer1.h"
#include "twi.h"

void robot_set_velocity(int8_t left, int8_t right) {
    twi_start();
    twi_send_slave_address_write(ROBOT_SLAVE_ADDRESS);
    twi_send_byte(ROBOT_COMMAND_SET_VELOCITY);
    twi_send_byte(right);
    twi_send_byte(left);
    twi_stop();
}

void robot_set_led(uint8_t red, uint8_t blue) {
    // led values 0..63
    red >>= 2;
    blue >>= 2;

    twi_start();
    twi_send_slave_address_write(ROBOT_SLAVE_ADDRESS);
    twi_send_byte(ROBOT_COMMAND_SET_LED);
    twi_send_byte(red);
    twi_send_byte(blue);
    twi_stop();
}

void robot_drive_request(int8_t distance) {
    twi_start();
    twi_send_slave_address_write(ROBOT_SLAVE_ADDRESS);
    twi_send_byte(ROBOT_COMMAND_DRIVE_REQUEST);
    twi_send_byte(distance);
    twi_stop();
}

void robot_turn_request(int8_t angle) {
    twi_start();
    twi_send_slave_address_write(ROBOT_SLAVE_ADDRESS);
    twi_send_byte(ROBOT_COMMAND_TURN_REQUEST);
    twi_send_byte(angle);
    twi_stop();
}

void robot_get_odometry() {
    uint8_t data[6];
    uint8_t i;

    // tell slave we need odometry data
    twi_start();
    twi_send_slave_address_write(ROBOT_SLAVE_ADDRESS);
    twi_send_byte(ROBOT_COMMAND_ODOMETRY);

    // start reading
    twi_start();
    twi_send_slave_address_read(ROBOT_SLAVE_ADDRESS);
    for (i = 0; i < 5; i++) {
        data[i] = twi_receive_byte_ack();
    }
    data[5] = twi_receive_byte_nack();
    twi_stop();

    uart_printf(
            "odometry: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x",
            data[0],
            data[1],
            data[2],
            data[3],
            data[4],
            data[5]
            );
}

void robot_set_odometry(int8_t xlow, int8_t xheigh, int8_t ylow, int8_t
        yheigh, int8_t alphalow, int8_t alphaheigh) {
    twi_start();
    twi_send_slave_address_write(ROBOT_SLAVE_ADDRESS);
    twi_send_byte(ROBOT_COMMAND_ODOMETRY);
    twi_send_byte(xlow);
    twi_send_byte(xheigh);
    twi_send_byte(ylow);
    twi_send_byte(yheigh);
    twi_send_byte(alphalow);
    twi_send_byte(alphaheigh);
    twi_stop();
}

void robot_get_sensor(void) {
    uint8_t data[8];
    uint8_t i;

    // tell slave we need sensor data
    twi_start();
    twi_send_slave_address_write(ROBOT_SLAVE_ADDRESS);
    twi_send_byte(ROBOT_COMMAND_GET_SENSOR);

    // get sensor data (repeated start)
    twi_start();
    twi_send_slave_address_read(ROBOT_SLAVE_ADDRESS);
    for (i = 0; i < 7; i++) {
        data[i] = twi_receive_byte_ack();
    }
    data[7] = twi_receive_byte_nack();
    twi_stop();

    // redo request because of buffering

    // tell slave we need sensor data
    twi_start();
    twi_send_slave_address_write(ROBOT_SLAVE_ADDRESS);
    twi_send_byte(ROBOT_COMMAND_GET_SENSOR);

    // get sensor data (repeated start)
    twi_start();
    twi_send_slave_address_read(ROBOT_SLAVE_ADDRESS);
    for (i = 0; i < 7; i++) {
        data[i] = twi_receive_byte_ack();
    }
    data[7] = twi_receive_byte_nack();
    twi_stop();

    uart_printf(
            "sensor: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x",
            data[0],
            data[1],
            data[2],
            data[3],
            data[4],
            data[5],
            data[6],
            data[7]
            );
}

void robot_set_bar_level(uint8_t value) {
    value = value / (256 / (BAR_LEVEL_UP - BAR_LEVEL_DOWN));
    timer1_set_ocr(BAR_LEVEL_DOWN + value);
}

void robot_raise_bar(void) {
    uint16_t ocr = timer1_get_ocr();
    timer1_set_ocr(ocr + BAR_LEVEL_STEPS);
}

void robot_lower_bar(void) {
    uint16_t ocr = timer1_get_ocr();
    timer1_set_ocr(ocr - BAR_LEVEL_STEPS);
}

void robot_custom(uint8_t *senddata, uint8_t sendsize, uint8_t readsize) {
    // note: array will be allocated on stack
    uint8_t data[readsize];
    uint8_t i;

    // send custom data
    twi_start();
    twi_send_slave_address_write(ROBOT_SLAVE_ADDRESS);
    for (i = 0; i < sendsize; i++) {
        twi_send_byte(senddata[i]);
    }

    // receive custom data if any
    if (readsize > 0) {
        twi_start();
        twi_send_slave_address_read(ROBOT_SLAVE_ADDRESS);
        for (i = 0; i < readsize - 1; i++) {
            data[i] = twi_receive_byte_ack();
        }
        data[readsize - 1] = twi_receive_byte_nack();
    }

    twi_stop();

    // print received data if any
    if (readsize > 0) {
        uart_printf_nole("custom: ");
        for (i = 0; i < readsize; i++) {
            uart_printf_nole("0x%02x", data[i]);
            if (i < readsize - 1) {
                uart_printf_nole(" ");
            }
        }
        // send default lineending
        uart_printf("");
    }
}
