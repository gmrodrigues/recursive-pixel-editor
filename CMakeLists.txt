cmake_minimum_required(VERSION 3.16)
project(PixelRecursor)

set(CMAKE_CXX_STANDARD 17)

# Source files
set(SOURCES
    src/main.cpp
    src/PixelEditor.cpp
    src/Palette.cpp
    src/RecursiveRenderer.cpp
)

# Headers
set(HEADERS
    src/PixelEditor.h
    src/Palette.h
    src/RecursiveRenderer.h
)

# Check if we're building with Emscripten
if(EMSCRIPTEN)
    # Emscripten-specific settings
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    
    # SDL2 flags for Emscripten
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS='[\"_main\"]'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_RUNTIME_METHODS='[\"ccall\",\"cwrap\"]'")
    
    # Create executable
    add_executable(pixelrecursor ${SOURCES} ${HEADERS})
    
    # Set output name
    set_target_properties(pixelrecursor PROPERTIES OUTPUT_NAME "pixelrecursor")
    
else()
    # Native build - find SDL2
    find_path(SDL2_INCLUDE_DIRS SDL2/SDL.h
        HINTS /usr/include /usr/local/include)
    find_library(SDL2_LIBRARIES SDL2
        HINTS /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu)
    
    if(NOT SDL2_INCLUDE_DIRS OR NOT SDL2_LIBRARIES)
        message(FATAL_ERROR "SDL2 not found! Please install libsdl2-dev")
    endif()
    
    # Create executable
    add_executable(pixelrecursor ${SOURCES} ${HEADERS})
    
    # Link SDL2
    target_link_libraries(pixelrecursor ${SDL2_LIBRARIES})
    target_include_directories(pixelrecursor PRIVATE ${SDL2_INCLUDE_DIRS})
endif()

# Include directories
target_include_directories(pixelrecursor PRIVATE src)
