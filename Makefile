
EXE = main.out
CC = gcc
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR)/
LFLAGS = -lSDL_image 

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


all: $(EXE)  

$(EXE): $(OBJ)
	$(CC) $(LFLAGS) $^ -o $(EXE)	
	@echo "Build done."

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $< $(CFLAGS) -c -o $@
	@echo -e "Compilation done.\n" 

clean:
	rm -rf $(BUILD_DIR)

