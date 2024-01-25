.PHONY: all clean
CC= gcc
CFLAGS= -Wall

SOURCE= main.c $(wildcard components/*.c)
OBJ= $(SOURCE:.c=.o)
TARGET= main

all: $(TARGET) $(OBJ_DIR)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $@

clean:
	rm $(OBJ)
	rm $(TARGET)