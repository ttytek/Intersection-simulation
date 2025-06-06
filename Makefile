CC = gcc
CFLAGS = -Wall -Wextra -O2 -I./src/c
SRC_DIR = src/c
BIN_DIR = bin
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/buffer.c $(SRC_DIR)/sim.c $(SRC_DIR)/renderer.c $(SRC_DIR)/utils.c
OBJS = $(SRCS:.c=.o)
TARGET = $(BIN_DIR)/sim

all: $(TARGET)


# Link object files into final binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(SRC_DIR)/*.o

test_runner:
	gcc  -Isrc/c -Itest/Unity/src -DID_LEN=10 -DBUFFER_SIZE=4  test/test_buffer.c test/test_simulation.c test/test_main.c  src/c/buffer.c src/c/sim.c test/Unity/src/unity.c  -o test_runner

.PHONY: all clean