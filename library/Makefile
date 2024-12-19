# Compiler and flags
CC := gcc
LDFLAGS := -shared

# Output directories
BUILD_DIR := build
BIN_DIR := bin

# Source files
LOGGER_SRC := logger.c
FILESYSTEM_SRC := filesystem.c

# Output shared libraries
LOGGER_LIB := $(BIN_DIR)/liblogger.so
FILESYSTEM_LIB := $(BIN_DIR)/libfilesystem.so

# Windows output (optional, if cross-compiling)
LOGGER_LIB_WIN := $(BIN_DIR)/logger.dll
FILESYSTEM_LIB_WIN := $(BIN_DIR)/filesystem.dll

# Ensure output directories exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Default target
all: $(LOGGER_LIB) $(FILESYSTEM_LIB)

# Compile logger shared library
$(LOGGER_LIB): $(LOGGER_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# Compile filesystem shared library
$(FILESYSTEM_LIB): $(FILESYSTEM_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# Windows shared libraries (optional)
windows: $(LOGGER_LIB_WIN) $(FILESYSTEM_LIB_WIN)

$(LOGGER_LIB_WIN): $(LOGGER_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -shared -o $@ $<

$(FILESYSTEM_LIB_WIN): $(FILESYSTEM_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -shared -o $@ $<

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all windows clean
