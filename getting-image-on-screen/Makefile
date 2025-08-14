# SDL2 Game Makefile
# Simple and lazy compilation setup

# Compiler and flags
CC = gcc
CFLAGS = $(shell pkg-config --cflags sdl2) -Wall -Wextra -std=c99
LIBS = $(shell pkg-config --libs sdl2)

# Project settings
TARGET = game
SOURCES = main.c
# Add more source files here: main.c player.c enemy.c

# Default target - just type 'make'
all: $(TARGET)

# Compile the game
$(TARGET): $(SOURCES)
	$(CC) -o $(TARGET).exe $(SOURCES) $(CFLAGS) $(LIBS)
	@echo "✅ Build successful! Run with: ./$(TARGET).exe"

# Quick build and run
run: $(TARGET)
	./$(TARGET).exe

# Clean up compiled files
clean:
	rm -f $(TARGET).exe *.o
	@echo "🧹 Cleaned up!"

# Debug build with extra info
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)
	@echo "🐛 Debug build ready!"

# Release build with optimizations
release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)
	@echo "🚀 Release build ready!"

# Check if SDL2 is properly installed
check:
	@echo "Checking SDL2 installation..."
	@pkg-config --exists sdl2 && echo "✅ SDL2 found!" || echo "❌ SDL2 not found!"
	@pkg-config --modversion sdl2

# Install dependencies (for MSYS2)
install-deps:
	pacman -S mingw-w64-ucrt-x86_64-SDL2

# Show help
help:
	@echo "SDL2 Makefile Commands:"
	@echo "  make         - Build the game"
	@echo "  make run     - Build and run the game"
	@echo "  make clean   - Remove compiled files"
	@echo "  make debug   - Build with debug info"
	@echo "  make release - Build optimized version"
	@echo "  make check   - Verify SDL2 installation"
	@echo "  make help    - Show this help"

# Phony targets (not files)
.PHONY: all run clean debug release check install-deps help
