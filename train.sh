#!/bin/bash

echo "Training : $1"   

for i in {1..100}; 
do 
    echo $i; 
    ./main.out >> /dev/null
done
