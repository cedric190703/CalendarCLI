# Compiler options
CC := gcc
CFLAGS := -fsanitize=address -g -lm

# Directories
BUILD_DIR := build
UTILS_DIR := utils

# Source files
MAIN_SOURCE := main.c
UTILS_SOURCE := $(wildcard $(UTILS_DIR)/*.c)

# Create objects
OBJECTS := $(patsubst $(UTILS_DIR)/%.c,$(BUILD_DIR)/%.o,$(UTILS_SOURCE))

# Create object file directory
OBJECTS_DIRS := $(sort $(dir $(OBJECTS)))

# Define targets
EXECUTABLE := calendar

# Default target
.DEFAULT_GOAL := $(EXECUTABLE)

# Build rule for object files
$(BUILD_DIR)/%.o : $(UTILS_DIR)/%.c
	@mkdir -p $(OBJECTS_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link rule for the executable
$(EXECUTABLE): $(OBJECTS) $(MAIN_SOURCE)
	$(CC) $(CFLAGS) $^ -o $@

# Phony targets
.PHONY: clean

# Clean target
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)