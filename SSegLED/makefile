upload: main.hex
	avrdude -C /etc/avrdude.conf -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex:i

main.hex: combined.o
	avr-objcopy -O ihex -j.text -j.data combined.o main.hex

combined.o: main.o ssegled.o atm328util.o time.o
	avr-gcc -Os -mmcu=atmega328 main.o ssegled.o atm328util.o time.o -o combined.o

main.o: main.c ssegled.h atm328util.h time.h
	avr-gcc -Os -c -mmcu=atmega328 main.c

time.o: time.c time.h
	avr-gcc -Os -c -mmcu=atmega328 time.c

atm328util.o: atm328util.c atm328util.h
	avr-gcc -Os -c -mmcu=atmega328 atm328util.c

ssegled.o: ssegled.c ssegled.h atm328util.h time.h 
	avr-gcc -Os -c -mmcu=atmega328 ssegled.c




