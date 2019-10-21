#Script for burning code directly on AVR microcontrollers
#Based on programs: avrdude and avr-gcc
#Author: Bartłomiej Kliś, 21.02.2019 
#!/bin/bash

#Default setup:
microcontroller="atmega16"
programmer="usbasp"

while getopts "m:a:hv" option
do
	case $option in
	m) m_option=$OPTARG;;
	a) a_option=$OPTARG;;
	h) h_option=1;;
	v) v_option=1;;
	*) echo "Usage: $0 [-m {microcontroller type (atmega8 - default)}] [-a {programer (usbasp - default)}] [-v (verbose mode)] [-h (short description)]"
	exit -1;;
	esac
done

shift $(($OPTIND - 1))

if [ ! -e $1 ] || [ -z $1 ]
then
        echo "[ERROR] No imput \".c\" file."
	echo "Usage: $0 [-m {microcontroller type (atmega8 - default)}] [-a {programer (usbasp - default)}] [-v (verbose mode)] [-h (short description)]"
        exit -1
fi

if [ ! -z $h_option ]
then
	echo "[HELP] Quick description:"
	echo "Usage: $0 [-m {microcontroller type (atmega8 - default)}] [-a {programer (usbasp - default)}] [-v (verbose mode)] [-h (short description)]"
	echo "Script compile input \".c\" file to executable then converts it's to \".hex\" file. After this steps script will burn it to connected avr microcontroller. more..."
	exit 0
fi

if [ ! -z $v_option ]
then
	echo "[START] AVR-Burner 2019, BK"
fi

if [ ! -z $m_option ]
then
	microcontroller=$m_option
fi
if [ ! -z $v_option ]
then
	echo "[INFO] Microcontroller: $microcontroller"
fi

if [ ! -z $a_option ]
then
        programmer=$a_option
fi
if [ ! -z $v_option ]
then
	echo "[INFO] Programmer: $programmer"
fi

if [ ! -z $v_option ]
then
        avr-gcc -mmcu=$microcontroller $1 -o avrprog.o
	avr-objcopy -j .text -j .data -O ihex avrprog.o avrprog.hex
	sudo avrdude -c $programmer -p $microcontroller
	sudo avrdude -c $programmer -p $microcontroller -u -U flash:w:avrprog.hex
else
	avr-gcc -mmcu=$microcontroller $1 -o avrprog.o &> /dev/null
        avr-objcopy -j .text -j .data -O ihex avrprog.o avrprog.hex &> /dev/null
        sudo avrdude -c $programmer -p $microcontroller &> /dev/null
        sudo avrdude -c $programmer -p $microcontroller -u -U flash:w:avrprog.hex &> /dev/null
fi

