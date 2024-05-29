# Compiler
CC:=gcc

# The target binary file
TARGET:=test

# Directories
SRC_DIR:=../src
TEST_DIR:=.
UNITY_DIR:=./Unity/src
INCLUDE_DIRS:=../include $(UNITY_DIR)

# Source files
SRC_FILES:=$(SRC_DIR)/util.c $(TEST_DIR)/test_util.c $(UNITY_DIR)/unity.c

# Include flags
INCLUDE_FLAGS := $(addprefix -I, $(INCLUDE_DIRS))

# Compiler flags
C_FLAGS := -Wall $(INCLUDE_FLAGS)

# Build the target
all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CC) $(C_FLAGS) $^ -o $@

clean:
	rm -rf $(TARGET)

.PHONY: clean all
