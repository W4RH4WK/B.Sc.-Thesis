#ifndef __CONFIG_H_
#define __CONFIG_H_

// controller check
#ifndef __AVR_ATmega32__
    #error Target should be ATmega32
#endif

// controller clock
#define F_CPU 16E6

// debug output
#define LOG

// buffer size
#define COMMAND_BUFFER_LENGTH 16

// line ending
#define LINE_ENDING "\r\n"

// robot slave addr
#define ROBOT_SLAVE_ADDRESS 0xd2

// bit macros
#define gBit(A,B) ((A>>B) & 1)      // get bit
#define sBit(A,B) (A |= (1<<B))     // set bit
#define cBit(A,B) (A &= ~(1<<B))    // clear bit
#define tBit(A,B) (A ^= (1<<B))     // toggle bit

#endif
