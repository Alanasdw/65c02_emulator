.PHONY: all clean
CC= gcc
CFLAGS= -Wall

SOURCE= writer.c
OBJ= $(SOURCE:.c=.o)
TARGET= writer

all: $(TARGET) $(OBJ_DIR)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $@

clean:
	rm $(OBJ)
	rm $(TARGET)