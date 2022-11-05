
EXE = solver.out
CC = gcc
PROJET_NAME = Solver
CFLAGS = -Wall -Wextra -Werror

all:
	@echo -e "\n---- Projet $(PROJET_NAME) ----\n"
	@echo -e "\tCompiling : solving.c..."
	@$(CC) solving.c $(CFLAGS) -c -o solving.o
	@echo -e "\tCompiling : file.c..."
	@$(CC) file.c $(CFLAGS) -c -o file.o
	@echo -e "\tCompiling : main.c...\n"
	@$(CC) main.c $(CFLAGS) -c -o main.o
	@echo -e "Link every file...\n"
	@$(CC) main.o file.o solving.o -o $(EXE) 
	@echo -e "Build finish"

clean:
	@echo -e "\n---- Projet $(PROJET_NAME) ----\n"
	@rm -rf *.o
	@echo -e "\t*.o/ delete."
	@rm -rf *.bmp
	@echo -e "\t*.bmp delete."
	@rm -f $(EXE)
	@echo -e "\t$(EXE) delete." 
	@echo -e "\nClean Finish.\n"
