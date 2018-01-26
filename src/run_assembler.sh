#!/bin/sh

if [ "$#" -eq  "0" ]
then
	make clean && make && ./assemble ../tests/test_cases_assembler/add01.s add01.bin        
else
    make clean && make && ./assemble ../tests/test_cases/"$1".s "$1".bin    
fi
