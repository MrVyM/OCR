#!/bin/sh   

list=$(ls grids/)
echo "\nLancement des tests...\n"
for element in $list    
do   
	echo "Lancement du Sudoku Solver : ./solver grids/$element"
        if ./solver.out grids/$element; then
                cat grids/$element.result
        fi
        echo ""
done
