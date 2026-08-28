CC = gcc

CFLAGS = -std=c11 -O2 -Wall -Werror -Wextra -pedantic
DEBUGFLAGS = -std=c11 -O0 -g -Wall -Werror -Wextra -pedantic

SRC = $(wildcard src/*.c)
TARGET = minish

.PHONY: all clean debug format

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

debug:
	$(CC) $(DEBUGFLAGS) $(SRC) -o $(TARGET)

format:
	clang-format -i $(SRC)
