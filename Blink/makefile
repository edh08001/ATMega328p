upload: main.hex
	avrdude -C /etc/avrdude.conf -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex:i

main.hex: combined.o
	avr-objcopy -O ihex -j.text -j.data combined.o main.hex

combined.o: main.o util.o
	avr-gcc -Os -mmcu=atmega328 main.o util.o -o combined.o 

main.o: main.c util.h atm328pins.h 
	avr-gcc -Os -c -mmcu=atmega328 main.c 

util.o: util.c util.h
	avr-gcc -Os -c -mmcu=atmega328 util.c



