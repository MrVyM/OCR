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
	$(CC) $(CFLAGS) Src/CaMa/CaMa.c -o $(BUILD_DIR)/CaMa.o

clean: 
	rm -rf *.o

