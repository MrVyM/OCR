#!/bin/sh   

list="00 01 02 03 04 05 06 no_format no_solvable"
echo "\nLancement des tests...\n"
for element in $list    
do   
	echo "Lancement du Sudoku Solver : ./solver grid_$element"
        if ./solver.out grids/grid_$element; then
                cat grids/grid_$element.result
        fi
        echo ""
done
