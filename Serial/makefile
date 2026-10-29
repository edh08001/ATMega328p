upload: main.hex
	avrdude -C /etc/avrdude.conf -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex:i

main.hex: combined.o
	avr-objcopy -O ihex -j.text -j.data combined.o main.hex

combined.o: main.o time.o
	avr-gcc -Os -mmcu=atmega328 main.o time.o -o combined.o

main.o: main.c time.h
	avr-gcc -Os -c -mmcu=atmega328 main.c

time.o: time.c time.h
	avr-gcc -Os -c -mmcu=atmega328 time.c
