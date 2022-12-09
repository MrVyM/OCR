#!/bin/bash

j=0

while [[ 1 ]]
do 
	j=$((j+2))
	echo -e "------------------------- $j -------------------------\n"
	./main.out
done