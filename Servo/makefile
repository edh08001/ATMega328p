upload: main.hex
	avrdude -C /etc/avrdude.conf -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex:i

main.hex: combined.o
	avr-objcopy -O ihex -j.text -j.data combined.o main.hex

combined.o: main.o servo.o io.o
	avr-gcc -Os -mmcu=atmega328 main.o servo.o io.o -o combined.o

main.o: main.c servo.h
	avr-gcc -Os -c -mmcu=atmega328 main.c

servo.o: servo.c servo.h io.h 
	avr-gcc -Os -c -mmcu=atmega328 servo.c

io.o: io.c io.h
	avr-gcc -Os -c -mmcu=atmega328 io.c
