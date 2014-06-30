build:
	avr-gcc -mmcu=atmega32 -Os -o bin *.c
	avr-objcopy -O ihex bin hex
	avr-size -C --mcu=atmega32 bin

flash:
	avrdude -p m32 -P /dev/ttyACM0 -c avrisp2 -B 10 -Uflash:w:hex

all: build flash

clean:
	rm -f bin
	rm -f hex
	rm -f *.o

fuse:
	avrdude -p m32 -P /dev/ttyACM0 -c avrisp2 -B 10 -U lfuse:w:0xbf:m -U hfuse:w:0x89:m
