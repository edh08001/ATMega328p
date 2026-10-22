upload: main.hex
	avrdude -C /etc/avrdude.conf -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex:i

main.hex: combined.o
	avr-objcopy -O ihex -j.text -j.data combined.o main.hex

combined.o: main.o atm328util.o
	avr-gcc -Os -mmcu=atmega328 main.o atm328util.o -o combined.o

main.o: main.c atm328util.h atm328pins.h ssegled.h
	avr-gcc -Os -c -mmcu=atmega328 main.c

atm328util.o: atm328util.c atm328util.h 
	avr-gcc -Os -c -mmcu=atmega328 atm328util.c




