CC ?= clang
CFLAGS ?= -std=c17 -Wall -Wextra -g $(shell pkg-config --cflags sdl3)
LDFLAGS ?= $(shell pkg-config --libs sdl3)

TARGET = game
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) $(TARGET).dSYM

.PHONY: all run clean
