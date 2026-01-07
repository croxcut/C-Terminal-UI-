CC      = gcc
CFLAGS  = -std=c11

TARGET  = main

SRC     = $(wildcard *.c)

OBJ     = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	start cmd /k "$(TARGET).exe"
	
clean:
	rm -f $(OBJ) $(TARGET)

re: clean all

.PHONY: all clean re
