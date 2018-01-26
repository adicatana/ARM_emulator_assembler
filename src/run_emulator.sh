#!/bin/sh

if [ "$#" -eq  "0" ]
then
	make clean && make && ./emulate ../tests/test_cases/add01        
else
    make clean && make && ./emulate ../tests/test_cases/"$1"    
fi
