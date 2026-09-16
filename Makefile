
CC = gcc

CPPFLAGS = -Iinclude
CFLAGS = -Wall -Wextra -Werror -std=c11 -O3 -g

TARGET = apc

SRC = $(wildcard src/*.c)
OBJ = $(notdir $(SRC:.c=.o))
HEADERS = include/apc.h include/dll.h

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJ) -o $@

%.o: src/%.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
