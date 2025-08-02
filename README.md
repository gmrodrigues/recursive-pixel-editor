# PixelRecursor

A recursive pixel art editor written in C++ with SDL2, compilable to WebAssembly using Emscripten.

This is an educational example of a compiled C++ graphics application which runs in the browser (WebAssembly) or as a traditional native executable.

It demonstrates a rendering technique using a grid of 8x8 pixels, where each pixel in the final display becomes a miniature version of the full image — creating a recursive visual effect.

This kind of project could also be implemented effectively in JavaScript using the Canvas API. In both environments, you would typically manage the drawing state in an internal data structure and render to the screen on each frame. The choice of C++ and SDL2 here reflects a preference for low-level control and native code structure rather than a fundamental technical necessity.

## Demo

https://gmrodrigues.github.io/rpixed/

## Screenshots

![Screenshot](./screenshots/2025-08-01_19-02.png)  
![Screenshot](./screenshots/2025-08-01_19-04.png)  
![Screenshot](./screenshots/2025-08-01_19-06.png)  
![Screenshot](./screenshots/2025-08-01_19-10.png)

## Features

- **8x8 Pixel Editor**: Click to draw with your mouse on an 8x8 grid
- **16-Color Palette**: PICO-8 inspired color palette with visual selection
- **Recursive Visualization**: Each pixel in your 8x8 design becomes a copy of the entire image, creating a 64x64 recursive pattern
- **Cross-Platform**: Runs natively on desktop or in web browsers via WebAssembly
- **Minimal Dependencies**: Only uses SDL2, no external libraries

## Controls

- **Left Click**: Paint pixels in the editor grid or select colors from the palette
- **C Key**: Clear the entire canvas
- **Mouse**: Navigate between the editor grid and color palette

## More on WebAssembly

In WebAssembly (WASM), your compiled C++ application runs inside a lightweight virtual machine embedded in the browser. WebAssembly provides a low-level, efficient binary format with access to a flat linear memory model, allowing structured control over your application state.

Unlike JavaScript, where canvas drawing is immediate-mode and you must manage rendering state explicitly, in WebAssembly you can structure memory and logic in ways more similar to traditional native applications. However, for simple 2D editors like this one, both JavaScript and WebAssembly can achieve similar results — and JavaScript is often more accessible and convenient for quick development.

## Building

### Prerequisites

#### For Native Build:
- CMake 3.16+
- SDL2 development libraries
- C++17 compatible compiler

**Ubuntu/Debian:**
```bash
sudo apt-get install libsdl2-dev cmake build-essential
```

**Fedora:**
```bash
sudo dnf install SDL2-devel cmake gcc-c++
```

**Arch Linux:**
```bash
sudo pacman -S sdl2 cmake gcc
```

#### For Web Build:
- [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)

### Building for Desktop

```bash
./build_native.sh
cd build_native
./pixelrecursor
```

### Building for Web

```bash
# Make sure Emscripten is activated
source /path/to/emsdk/emsdk_env.sh

./build_emscripten.sh
cd web
python3 -m http.server 8000
```

Then open `http://localhost:8000` in your browser.

## Project Structure

```
├── src/
│   ├── main.cpp              # Main application and SDL setup
│   ├── PixelEditor.h/.cpp    # 8x8 pixel grid editor
│   ├── Palette.h/.cpp        # 16-color palette management
│   └── RecursiveRenderer.h/.cpp # Recursive visualization renderer
├── assets/                   # Asset directory (currently empty)
├── CMakeLists.txt           # Build configuration
├── build_native.sh          # Native build script
├── build_emscripten.sh      # Web build script
└── README.md               # This file
```

## How It Works

1. **Editor Grid**: The main 8x8 grid where you create your pixel art
2. **Color Palette**: 16 predefined colors in a 4x4 grid for selection
3. **Recursive Display**: The 64x64 output where each "pixel" of your 8x8 design is replaced by the entire 8x8 image, creating a fractal-like recursive pattern

## Technical Details

- **Language**: C++17
- **Graphics**: SDL2 for cross-platform rendering
- **Build System**: CMake with Emscripten support
- **Web Target**: WebAssembly (WASM) with HTML5 Canvas
- **Architecture**: Component-based design with separate classes for editing, palette, and rendering

## Future Enhancements

- PNG export functionality using Emscripten file APIs
- Multiple levels of recursion (recursive recursion!)
- Undo/redo functionality
- Save/load project files
- Animation support
- Custom palette editing

## License

This project is open source. Feel free to modify and distribute.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

# recursive-pixel-editor
