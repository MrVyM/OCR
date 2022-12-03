#!/bin/sh   

cd assets/
list=$(ls *.jpeg)
angle=15
cd ..
echo "\nLancement des tests...\n"
rm -rf tests
mkdir tests
for element in $list    
do   
        mkdir tests/$element
	echo "Lancement du OCR : ./main assets/$element $angle"
        if ./main.out assets/$element $angle; then
                echo "[OCR] Return Code : $?"
        fi
        mv *.bmp ./tests/$element
        echo ""
done
