#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Palette {
public:
    Palette();
    ~Palette() = default;

    // Get color by index (0-15)
    SDL_Color getColor(int index) const;
    
    // Get current selected color index
    int getCurrentColorIndex() const { return currentColorIndex; }
    
    // Set current color index
    void setCurrentColorIndex(int index);
    
    // Get total number of colors
    int getColorCount() const { return static_cast<int>(colors.size()); }
    
    // Render palette UI
    void render(SDL_Renderer* renderer, int x, int y, int cellSize);
    
    // Handle mouse click on palette
    bool handleClick(int mouseX, int mouseY, int paletteX, int paletteY, int cellSize);

private:
    std::vector<SDL_Color> colors;
    int currentColorIndex;
    
    void initializePico8Colors();
};
