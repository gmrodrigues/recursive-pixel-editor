#include "Palette.h"

Palette::Palette() : currentColorIndex(0) {
    initializePico8Colors();
}

void Palette::initializePico8Colors() {
    // PICO-8 inspired 16-color palette
    colors = {
        {0, 0, 0, 255},         // Black
        {29, 43, 83, 255},      // Dark Blue
        {126, 37, 83, 255},     // Dark Purple
        {0, 135, 81, 255},      // Dark Green
        {171, 82, 54, 255},     // Brown
        {95, 87, 79, 255},      // Dark Grey
        {194, 195, 199, 255},   // Light Grey
        {255, 241, 232, 255},   // White
        {255, 0, 77, 255},      // Red
        {255, 163, 0, 255},     // Orange
        {255, 236, 39, 255},    // Yellow
        {0, 228, 54, 255},      // Green
        {41, 173, 255, 255},    // Blue
        {131, 118, 156, 255},   // Indigo
        {255, 119, 168, 255},   // Pink
        {255, 204, 170, 255}    // Peach
    };
}

SDL_Color Palette::getColor(int index) const {
    if (index >= 0 && index < static_cast<int>(colors.size())) {
        return colors[index];
    }
    return {0, 0, 0, 255}; // Default to black
}

void Palette::setCurrentColorIndex(int index) {
    if (index >= 0 && index < static_cast<int>(colors.size())) {
        currentColorIndex = index;
    }
}

void Palette::render(SDL_Renderer* renderer, int x, int y, int cellSize) {
    for (int i = 0; i < static_cast<int>(colors.size()); i++) {
        int col = i % 4;
        int row = i / 4;
        
        SDL_Rect rect = {
            x + col * cellSize,
            y + row * cellSize,
            cellSize,
            cellSize
        };
        
        // Fill with color
        SDL_Color color = colors[i];
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
        
        // Draw border
        if (i == currentColorIndex) {
            // Highlight selected color with thick white border
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            for (int border = 0; border < 2; border++) {
                SDL_Rect borderRect = {
                    rect.x - border,
                    rect.y - border,
                    rect.w + 2 * border,
                    rect.h + 2 * border
                };
                SDL_RenderDrawRect(renderer, &borderRect);
            }
        } else {
            // Normal border
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

bool Palette::handleClick(int mouseX, int mouseY, int paletteX, int paletteY, int cellSize) {
    int relativeX = mouseX - paletteX;
    int relativeY = mouseY - paletteY;
    
    if (relativeX < 0 || relativeY < 0) return false;
    
    int col = relativeX / cellSize;
    int row = relativeY / cellSize;
    
    if (col >= 4 || row >= 4) return false;
    
    int colorIndex = row * 4 + col;
    if (colorIndex < static_cast<int>(colors.size())) {
        setCurrentColorIndex(colorIndex);
        return true;
    }
    
    return false;
}
