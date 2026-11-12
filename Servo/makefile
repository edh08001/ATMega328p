upload: main.hex
	avrdude -C /etc/avrdude.conf -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex:i

main.hex: combined.o
	avr-objcopy -O ihex -j.text -j.data combined.o main.hex

combined.o: main.o pwm.o io.o time.o 
	avr-gcc -Os -mmcu=atmega328 main.o pwm.o io.o time.o -o combined.o

main.o: main.c pwm.h time.h
	avr-gcc -Os -c -mmcu=atmega328 main.c

pwm.o: pwm.c pwm.h io.h
	avr-gcc -Os -c -mmcu=atmega328 pwm.c

io.o: io.c io.h
	avr-gcc -Os -c -mmcu=atmega328 io.c

time.o: time.c time.h
	avr-gcc -Os -c -mmcu=atmega328 time.c
