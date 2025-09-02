
CC = gcc

CWARNINGS = -Wall -Wextra -Werror -Wpedantic
CFLAGS = -O2 -Iinclude 
RAYLIB_FLAGS = -lraylib -lm -lpthread -ldl -lGL -lrt -lX11

SRC = src
BIN = bin

FILE ?= main
TARGET = $(BIN)/$(FILE)

all: $(TARGET)

$(BIN):
	mkdir -p $@

$(BIN)/$(FILE): $(SRC)/$(FILE).c | $(BIN)
	$(CC) $(CFLAGS) -o $@ $< $(RAYLIB_FLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BIN)

.PHONY: all run clean
