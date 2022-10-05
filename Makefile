CC = gcc
OBJ = main.o
HEADER = Include/
CFLAGS = -c -Wall -I$(HEADER)
TARGET = Src/main.c
BUILD_DIR = Build

all: $(TARGET) CaMa
	$(CC) $(TARGET) $(CFLAGS) -o $(BUILD_DIR)/main.o
	$(CC) $(BUILD_DIR)/*.o -o final 

CaMa: 
	$(CC) $(CFLAGS) Src/CaMa/caMa.c -o $(BUILD_DIR)/caMa.o

clean: 
	rm -rf $(BUILD_DIR)/*

