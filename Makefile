CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Find all C source files in the src directory
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Generate a list of object files in the obj directory
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Name of the final executable
TARGET = $(BIN_DIR)/your_program.exe

# Default target: build the executable
all: $(TARGET)

# Linking step to generate the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@

# Compilation step to generate object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony target to avoid conflicts with file names
.PHONY: all clean