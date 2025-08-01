#include "RecursiveRenderer.h"

RecursiveRenderer::RecursiveRenderer(int baseSize, int outputSize) 
    : baseSize(baseSize), outputSize(outputSize) {
    scaleFactor = outputSize / baseSize;
}

void RecursiveRenderer::render(SDL_Renderer* renderer, const PixelEditor& editor, 
                              const Palette& palette, int offsetX, int offsetY) {
    const auto& pixelData = editor.getPixelData();
    
    // Render each pixel of the base grid as a scaled-down version of the entire image
    for (int y = 0; y < baseSize; y++) {
        for (int x = 0; x < baseSize; x++) {
            int sourceColorIndex = pixelData[y][x];
            
            // Only render recursive copy if the source pixel is not dark (not black/index 0)
            if (sourceColorIndex != 0) {
                int pixelX = offsetX + x * scaleFactor;
                int pixelY = offsetY + y * scaleFactor;
                
                // Get the color for this recursive copy from the source pixel
                SDL_Color sourceColor = palette.getColor(sourceColorIndex);
                
                renderPixelRecursive(renderer, editor, palette, pixelX, pixelY, scaleFactor, sourceColor);
            }
        }
    }
}

void RecursiveRenderer::renderPixelRecursive(SDL_Renderer* renderer, const PixelEditor& editor, 
                                           const Palette& palette, int x, int y, int size, SDL_Color sourceColor) {
    const auto& pixelData = editor.getPixelData();
    int pixelSize = size / baseSize;
    
    // If pixel size is too small, just fill with a single color
    if (pixelSize < 1) {
        pixelSize = 1;
    }
    
    for (int py = 0; py < baseSize; py++) {
        for (int px = 0; px < baseSize; px++) {
            int colorIndex = pixelData[py][px];
            
            // Only paint pixels that are not dark (not black/index 0) in the source image
            if (colorIndex != 0) {
                SDL_Rect rect = {
                    x + px * pixelSize,
                    y + py * pixelSize,
                    pixelSize,
                    pixelSize
                };
                
                // Use the source color for this recursive copy
                SDL_SetRenderDrawColor(renderer, sourceColor.r, sourceColor.g, sourceColor.b, sourceColor.a);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}
