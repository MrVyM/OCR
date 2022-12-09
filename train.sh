#!/bin/bash

j=0

while [[ 1 ]]
do 
	j=$((j+3))
	echo $j
	./main.out
done