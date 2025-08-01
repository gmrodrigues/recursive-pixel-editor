#pragma once
#include <SDL2/SDL.h>
#include <vector>

class PixelEditor {
public:
    PixelEditor(int gridSize = 8);
    ~PixelEditor() = default;

    // Get/Set pixel color at position
    int getPixel(int x, int y) const;
    void setPixel(int x, int y, int colorIndex);
    
    // Clear the grid
    void clear();
    
    // Render the editing grid
    void render(SDL_Renderer* renderer, int offsetX, int offsetY, int cellSize);
    
    // Handle mouse click on grid
    bool handleClick(int mouseX, int mouseY, int gridX, int gridY, int cellSize, int colorIndex);
    
    // Get grid size
    int getGridSize() const { return gridSize; }
    
    // Get pixel data for recursive rendering
    const std::vector<std::vector<int>>& getPixelData() const { return pixels; }

private:
    int gridSize;
    std::vector<std::vector<int>> pixels;
};
