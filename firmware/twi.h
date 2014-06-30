#ifndef __TWI_H_
#define __TWI_H_

#include "config.h"

#include <stdbool.h>
#include <stdint.h>

void twi_init(void);

void twi_start(void);

void twi_stop(void);

// addr in 8 bit format (7 bit addr + R/W)
bool twi_send_slave_address(uint8_t addr);

// addr in 8 bit format (7 bit addr + R/W)
bool twi_send_slave_address_write(uint8_t addr);

// addr in 8 bit format (7 bit addr + R/W)
bool twi_send_slave_address_read(uint8_t addr);

bool twi_send_byte(uint8_t data);

// receive byte
uint8_t twi_receive_byte_ack(void);

// receive last byte
uint8_t twi_receive_byte_nack(void);

#endif
