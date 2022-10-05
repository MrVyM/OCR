CC = gcc
OBJ = main.o
HEADER = include/
CFLAGS = -c -Wall -Wextra -Werror -pedantic -I$(HEADER)
TARGET = src/main.c
BUILD_DIR = build

all: $(TARGET) CaMa
	$(CC) $(TARGET) $(CFLAGS) -o $(BUILD_DIR)/main.o
	$(CC) $(BUILD_DIR)/*.o -o final 

CaMa: 
	$(CC) $(CFLAGS) src/CaMa/caMa.c -o $(BUILD_DIR)/caMa.o



clean: 
	rm -rf $(BUILD_DIR)/*

