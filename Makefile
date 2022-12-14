
PROJET_NAME = OCR
EXE = main.out
CC = gcc
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TESTS_DIR = tests

# add -g argument just after the = of the CFLAGS for debugging with GDB

CFLAGS = -g `pkg-config --cflags sdl2 SDL2_image gtk+-3.0` -Wall -Wextra -I $(INCLUDE_DIR)/
LFLAGS = `pkg-config --libs sdl2 SDL2_image gtk+-3.0`

# find source file
SRC = $(shell find $(SRC_DIR) -type f -name '*.c')
# find source directory
SEARCH_DIR = $(shell find $(SRC_DIR) -type d)

# construct buid directory
$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(SEARCH_DIR)))


# Change the source file
TEMP_OBJ = $(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(SRC))
OBJ = $(patsubst %.c,%.o, $(TEMP_OBJ))


all: title $(EXE)
	@echo -e "\nMake Finish.\n"

run: all
	@./$(EXE)

help: 
	@echo -e "build : Rebuild the $(EXE) file."
	@echo -e "compile : Compile the *.c from $(SRC_DIR)."
	@echo -e "clean : Clean the project."
	@echo -e "all : (default) build and compile the project." 	

title:   
	@echo -e "\n---- Projet $(PROJET_NAME) ----\n"
	@echo -e "\tSource : $(SRC_DIR)"
	@echo -e "\tInclude : $(INCLUDE_DIR)"
	@echo -e "\tExecutable : $(EXE)\n"

compile: title $(OBJ)
	@echo -e "\nCompile Finish.\n"

build: title $(EXE)
	@echo -e "\nBuild Finish.\n"

$(EXE): $(OBJ)
	@$(CC) $^ $(LFLAGS) -o $(EXE) -lm
	@echo -e "\nExecutable $(EXE) done."

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $< $(CFLAGS) -c -o $@
	@echo "Compilation of $@ done." 

clean:
	@echo -e "\n---- Projet $(PROJET_NAME) ----\n"
	@rm -rf $(BUILD_DIR)
	@echo -e "\tBuild/ delete."
	@rm -rf $(TESTS_DIR)
	@echo -e "\tTests/ delete."
	@rm -rf *.bmp
	@echo -e "\t*.bmp delete."
	@rm -f $(EXE)
	@echo -e "\t$(EXE) delete." 
	@echo -e "\nClean Finish.\n"
	
tests: all
	@chmod a+x tests.sh 
	./tests.sh
