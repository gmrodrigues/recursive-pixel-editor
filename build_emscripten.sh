#!/bin/bash

# Build script for Emscripten
# Make sure you have Emscripten SDK installed and activated

# Create build directory
mkdir -p build_emscripten
cd build_emscripten

# Configure with Emscripten
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
emmake make

# Copy the generated files to a web directory
mkdir -p ../web
cp pixelrecursor.html ../web/index.html
cp pixelrecursor.js ../web/
cp pixelrecursor.wasm ../web/

echo "Build complete! Files are in the 'web' directory."
echo "You can serve the web directory with a local HTTP server."
echo "For example: python3 -m http.server 8000"
