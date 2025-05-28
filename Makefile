CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC_DIR = src/c
BIN_DIR = bin
SRC = $(SRC_DIR)/sim.c
TARGET = $(BIN_DIR)/sim

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean