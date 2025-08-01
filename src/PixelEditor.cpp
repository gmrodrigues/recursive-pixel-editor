#include "PixelEditor.h"

PixelEditor::PixelEditor(int gridSize) : gridSize(gridSize) {
    pixels.resize(gridSize, std::vector<int>(gridSize, 0));
}

int PixelEditor::getPixel(int x, int y) const {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        return pixels[y][x];
    }
    return 0;
}

void PixelEditor::setPixel(int x, int y, int colorIndex) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        pixels[y][x] = colorIndex;
    }
}

void PixelEditor::clear() {
    for (auto& row : pixels) {
        std::fill(row.begin(), row.end(), 0);
    }
}

void PixelEditor::render(SDL_Renderer* renderer, int offsetX, int offsetY, int cellSize) {
    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            SDL_Rect rect = {
                offsetX + x * cellSize,
                offsetY + y * cellSize,
                cellSize,
                cellSize
            };
            
            // Fill with background color (light gray for empty pixels)
            if (pixels[y][x] == 0) {
                SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
            } else {
                // This will be handled by the main application with palette colors
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
            
            // Draw grid lines
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

bool PixelEditor::handleClick(int mouseX, int mouseY, int gridX, int gridY, int cellSize, int colorIndex) {
    int relativeX = mouseX - gridX;
    int relativeY = mouseY - gridY;
    
    if (relativeX < 0 || relativeY < 0) return false;
    
    int pixelX = relativeX / cellSize;
    int pixelY = relativeY / cellSize;
    
    if (pixelX >= 0 && pixelX < gridSize && pixelY >= 0 && pixelY < gridSize) {
        setPixel(pixelX, pixelY, colorIndex);
        return true;
    }
    
    return false;
}
