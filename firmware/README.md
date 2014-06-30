# FT232 AVR Program

This code will run on the ATmega32 AVR located on FT232 v0.X boards. A simple
Makefile is provided to build and flash this program and to setup the fuses
properly.

## Modules
- `command` defines a buffer and logic for command execution
- `config`  contains global configuration
- `log`     defines a `log()` macro
- `robot`   contains all robot related functions
- `timer1`  helper for timer 1
- `twi`     helper for two wire interface (I2C)
- `uart`    helper functions, UART stream, UART receive interrupt

## Commands
Have a look at `command.c`, the `command_exec` function contains all available
commands and their code.

A command is issued as multiple bytes send to the controller over UART. The
first byte will determine the command, following bytes are treated as arguments
for the selected command. Commands are terminated with `\n`. `\r` will be
ignored to prevent double execution on `\r\n`.

Sensor-data and similar information will be written back as simple strings
terminated with `LINE_ENDING` defined in `config.h`.

This setup enables the user to communicate with the controller using a simple
terminal application like minicom or putty. Some of these applications require
you to hit CTRL + J to send a `\n`, RETURN will only send `\r`.
