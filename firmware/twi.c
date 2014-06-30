#include "twi.h"

#include <stdbool.h>
#include <stdint.h>
#include <util/twi.h>

#include "log.h"

void twi_init(void) {
    TWBR = 0x48; // 100 kHz
}

void twi_start(void) {
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!gBit(TWCR,TWINT));
}

void twi_stop(void) {
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

bool twi_send_slave_address(uint8_t addr) {
    TWDR = addr;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!gBit(TWCR,TWINT));
    return (TWSR & 0xf8) == TW_MT_DATA_ACK;
}

bool twi_send_slave_address_write(uint8_t addr) {
    cBit(addr, 0);
    return twi_send_slave_address(addr);
}

bool twi_send_slave_address_read(uint8_t addr) {
    sBit(addr, 0);
    return twi_send_slave_address(addr);
}

bool twi_send_byte(uint8_t data) {
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!gBit(TWCR,TWINT));
    return (TWSR & 0xf8) == TW_MT_DATA_ACK;
}

uint8_t twi_receive_byte_ack(void) {
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!gBit(TWCR,TWINT));
    return TWDR;
}

uint8_t twi_receive_byte_nack(void) {
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!gBit(TWCR,TWINT));
    return TWDR;
}
