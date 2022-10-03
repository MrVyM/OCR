# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS =

SRC = main.c file.c solving.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

solver: ${OBJ}

-include ${DEP}

.PHONY: clean

sudoku:
	gcc -Wall -Wextra -Werror -std=c99 -O1 -o solver *.c

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} *.result

# END
