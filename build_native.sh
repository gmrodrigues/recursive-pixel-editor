#!/bin/bash

# Build script for native compilation
# Make sure you have SDL2 development libraries installed
# Ubuntu/Debian: sudo apt-get install libsdl2-dev
# Fedora: sudo dnf install SDL2-devel
# Arch: sudo pacman -S sdl2

# Create build directory
mkdir -p build_native
cd build_native

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
make -j$(nproc)

echo "Build complete! Run ./pixelrecursor to start the application."
