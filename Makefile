CC := gcc
CFLAGS := -Iinclude
SRC_DIR := src
OBJ_DIR := obj
EXECUTABLE := main  # New name for the executable

# Get a list of all .c files in the source directory
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Create a list of object files corresponding to the source files
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(EXECUTABLE)

# Rule to compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the executable
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o ./$@

# Clean the generated files
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

.PHONY: all clean
