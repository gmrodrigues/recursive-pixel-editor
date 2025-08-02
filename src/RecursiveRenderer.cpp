#include "RecursiveRenderer.h"

RecursiveRenderer::RecursiveRenderer(int baseSize, int outputSize) 
    : baseSize(baseSize), outputSize(outputSize) {
    scaleFactor = outputSize / baseSize;
    startTime = SDL_GetTicks();  // Initialize start time
}

void RecursiveRenderer::render(SDL_Renderer* renderer, const PixelEditor& editor, 
                              const Palette& palette, int offsetX, int offsetY) {
    const auto& pixelData = editor.getPixelData();
    
    // Get the current pulsating scale factor
    float pulsatingScale = getPulsatingScaleFactor();
    int adjustedScaleFactor = static_cast<int>(scaleFactor * pulsatingScale);
    
    // Calculate centering offset to keep the pulsating image centered
    int centerOffsetX = (scaleFactor * baseSize - adjustedScaleFactor * baseSize) / 2;
    int centerOffsetY = (scaleFactor * baseSize - adjustedScaleFactor * baseSize) / 2;
    
    // Render each pixel of the base grid as a scaled-down version of the entire image
    for (int y = 0; y < baseSize; y++) {
        for (int x = 0; x < baseSize; x++) {
            int sourceColorIndex = pixelData[y][x];
            
            // Only render recursive copy if the source pixel is not dark (not black/index 0)
            if (sourceColorIndex != 0) {
                int pixelX = offsetX + centerOffsetX + x * adjustedScaleFactor;
                int pixelY = offsetY + centerOffsetY + y * adjustedScaleFactor;
                
                // Get the color for this recursive copy from the source pixel
                SDL_Color sourceColor = palette.getColor(sourceColorIndex);
                
                renderPixelRecursive(renderer, editor, palette, pixelX, pixelY, adjustedScaleFactor, sourceColor);
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

float RecursiveRenderer::getPulsatingScaleFactor() const {
    // Get current time in milliseconds
    Uint32 currentTime = SDL_GetTicks();
    float elapsedTime = (currentTime - startTime) / 1000.0f;  // Convert to seconds
    
    // Create a sinusoidal wave that completes one cycle every 10 seconds
    // sin(2π * t / 10) oscillates between -1 and 1
    // We map this to a scale range between 0.5 and 1.5 for a nice pulsating effect
    float sineWave = sin(2.0f * M_PI * elapsedTime / 10.0f);
    float scaleFactor = 1.5f + 0.5f * sineWave;  // Range: 1.0 to 2.0
    
    return scaleFactor;
}
