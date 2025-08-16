# SDL2 Game Makefile
# Simple and lazy compilation setup

# Compiler and flags
CC = gcc
CFLAGS = $(shell pkg-config --cflags sdl2) -Wall -Wextra -std=c99
LIBS = $(shell pkg-config --libs sdl2 | sed 's/-mwindows//')

# Project settings
TARGET = game
SOURCES = main.c
# Add more source files here: main.c player.c enemy.c

# Default target - just type 'make'
all: $(TARGET)

# Compile the game
$(TARGET): check-deps $(SOURCES)
	$(CC) -o $(TARGET).exe $(SOURCES) $(CFLAGS) $(LIBS)
	@echo "✅ Build successful! Run with: ./$(TARGET).exe"

# Check dependencies before building
check-deps:
	@pkg-config --exists sdl2 || (echo "❌ SDL2 missing! Run 'make setup' first" && exit 1)

# Quick build and run
run: $(TARGET)
	./$(TARGET).exe

# Clean up compiled files
clean:
	rm -f $(TARGET).exe *.o
	@echo "🧹 Cleaned up!"

# Debug build with extra info and console output
debug: CFLAGS += -g -DDEBUG
debug: LIBS = $(shell pkg-config --libs sdl2 | sed 's/-mwindows//')
debug: $(TARGET)
	@echo "🐛 Debug build ready with console output!"

# Release build with optimizations and no console
release: CFLAGS += -O2 -DNDEBUG
release: LIBS = $(shell pkg-config --libs sdl2)
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

# Smart check - auto-install if missing
setup:
	@echo "Setting up SDL2..."
	@if ! pkg-config --exists sdl2; then \
		echo "❌ SDL2 not found. Installing..."; \
		pacman -S mingw-w64-ucrt-x86_64-SDL2; \
	else \
		echo "✅ SDL2 already installed!"; \
	fi

# Show help
help:
	@echo "SDL2 Makefile Commands:"
	@echo "  make         - Build the game"
	@echo "  make run     - Build and run the game"
	@echo "  make clean   - Remove compiled files"
	@echo "  make debug   - Build with debug info"
	@echo "  make release - Build optimized version"
	@echo "  make check   - Verify SDL2 installation"
	@echo "  make setup   - Auto-install SDL2 if missing"
	@echo "  make help    - Show this help"

# Phony targets (not files)
.PHONY: all run clean debug release check install-deps help
