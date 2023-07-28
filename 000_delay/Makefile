# Compiler and flags
CC = sdcc
MCU = stc89
TARGET = main

# Directories
SRCDIR = .
BUILDDIR = build

# Source files
SRC = $(wildcard $(SRCDIR)/*.c)

# Object files
OBJ = $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.rel)

# Compiler flags
CFLAGS = -mmcs51 --model-small --std-sdcc89

# Linker flags
LFLAGS = $(CFLAGS)

# Determine the platform (Windows or Linux)
ifeq ($(OS),Windows_NT)
	# Windows platform
	FLASHER := stcgal.py
	FLASHER_ARGS := COM6
else
	# Linux platform
	FLASHER := stcgal
	FLASHER_ARGS := /dev/ttyUSB0
endif

# Flashing command
FLASH_CMD = $(FLASHER) -p $(FLASHER_ARGS) $(BUILDDIR)/$(TARGET).hex

all: $(BUILDDIR) $(TARGET).hex

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(TARGET).hex: $(OBJ)
	$(CC) $(LFLAGS) $(OBJ) -o $(BUILDDIR)/$(TARGET).ihx
	packihx $(BUILDDIR)/$(TARGET).ihx > $(BUILDDIR)/$(TARGET).hex

$(BUILDDIR)/%.rel: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

flash: $(BUILDDIR) $(TARGET).hex
	$(FLASH_CMD)

clean:
	@rm -rf $(BUILDDIR)

.PHONY: all clean flash

