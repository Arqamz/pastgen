# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Find all .c files recursively in SRC_DIR
SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = $(BIN_DIR)/parser

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Link the object files into the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile .c files into .o files
# Ensure the target directory exists before compiling
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | directories
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build and binary directories
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean directories
