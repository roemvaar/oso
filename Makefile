TARGET ?= rpi4

ifeq ($(TARGET), rpi4)
	X_DIR:=/usr/bin/xdev
    TRIPLE:=aarch64-none-elf
    ARCH:=cortex-a72
else ifeq ($(TARGET), qemu)
    $(error QEMU support is not implemented, yet)
endif

# Cross-compiler
XBIN_DIR:=$(X_DIR)/bin
CC=$(XBIN_DIR)/$(TRIPLE)-gcc
READELF=$(XBIN_DIR)/$(TRIPLE)-readelf
OBJCOPY=$(XBIN_DIR)/$(TRIPLE)-objcopy
OBJDUMP=$(XBIN_DIR)/$(TRIPLE)-objdump

# Directories
BUILD_DIR=build
SRC_DIR=src

# Compile options
# -ffunction-sections causes each function to be in a separate section (linker script relies on this)
WARNINGS=-Wall -Wextra -Wpedantic -Wno-unused-const-variable
C_FLAGS:=-g -pipe -static $(WARNINGS) -ffreestanding -nostartfiles -ffunction-sections\
	-mcpu=$(ARCH) -static-pie -Iinclude -mstrict-align -fno-builtin -mgeneral-regs-only

# -Wl, option tells g++ to pass 'option' to the linker with commas replaced by spaces
# doing this rather than calling the linker ourselves simplifies the compilation procedure
LD_FLAGS:=-Wl,-nmagic -Wl,-T$(SRC_DIR)/linker.ld

# Source files and include dirs
SOURCES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.S)

# Create .o and .d files for every .c and .S (hand-written assembly) file
OBJECTS := $(patsubst %.c, %.o, $(patsubst %.S, %.o, $(SOURCES)))
DEPENDS := $(patsubst %.c, %.d, $(patsubst %.S, %.d, $(SOURCES)))

# The first rule is the default, i.e., `make`, `make all`, and `make kernel8.img` mean the same
all: kernel8.img

clean:
	rm -rf $(BUILD_DIR)/*.*
	rm -f $(OBJECTS) $(DEPENDS)

kernel8.img: kernel8.elf
	$(OBJCOPY) $(BUILD_DIR)/$< -O binary $(BUILD_DIR)/$@

kernel8.elf: $(SRC_DIR)/linker.ld $(OBJECTS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(C_FLAGS) $(filter-out %.ld, $^) -o $(BUILD_DIR)/$@ $(LD_FLAGS)
	@$(OBJDUMP) -d $(BUILD_DIR)/kernel8.elf | fgrep -q q0 && printf "\n***** WARNING: SIMD INSTRUCTIONS DETECTED! *****\n\n" || true

debug: kernel8.elf kernel8.img
	$(OBJDUMP) -D $(BUILD_DIR)/kernel8.elf > $(BUILD_DIR)/objdump.txt
	$(READELF) -a $(BUILD_DIR)/kernel8.elf > $(BUILD_DIR)/readelf.txt

%.o: %.c Makefile
	$(CC) $(C_FLAGS) -MMD -MP -c $< -o $@

%.o: %.S Makefile
	$(CC) $(C_FLAGS) -MMD -MP -c $< -o $@

-include $(DEPENDS)
