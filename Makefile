# Directories
SRC_DIRS := virtualMachine library
BUILD_DIR := build
OUTPUT_BIN := vm

# Find all .c files in the specified directories
SRC_FILES := $(shell find $(SRC_DIRS) -name '*.c')
OBJ_FILES := $(patsubst %,$(BUILD_DIR)/%,$(SRC_FILES:.c=.o))

# Compiler and flags
CC := clang
CFLAGS := -g -O3

# Default target
all: $(OUTPUT_BIN)

# Create the binary by linking all object files
$(OUTPUT_BIN): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@

# Compile each .c file into a .o file
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(OUTPUT_BIN)

.PHONY: all clean
