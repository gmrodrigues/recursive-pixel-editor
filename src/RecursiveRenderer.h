#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include "PixelEditor.h"
#include "Palette.h"

class RecursiveRenderer {
public:
    RecursiveRenderer(int baseSize = 8, int outputSize = 64);
    ~RecursiveRenderer() = default;

    // Render the recursive pattern
    void render(SDL_Renderer* renderer, const PixelEditor& editor, const Palette& palette, 
                int offsetX, int offsetY);
    
    // Get output dimensions
    int getOutputSize() const { return outputSize; }
    int getBaseSize() const { return baseSize; }

private:
    int baseSize;
    int outputSize;
    int scaleFactor;
    Uint32 startTime;  // Time when renderer was created
    
    // Calculate current pulsating scale factor based on time
    float getPulsatingScaleFactor() const;
    
    void renderPixelRecursive(SDL_Renderer* renderer, const PixelEditor& editor, 
                             const Palette& palette, int x, int y, int size, SDL_Color sourceColor);
};
