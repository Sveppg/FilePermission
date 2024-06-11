#!/bin/sh

gcc -o FilePermi src/ChangePermfF.c src/escapesequenzen.h
if [ $? -eq 0 ]; then 
	./FilePermi
else
	echo "Check compiling status... something went wrong"
fi

