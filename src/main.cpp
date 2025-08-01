#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#include "PixelEditor.h"
#include "Palette.h"
#include "RecursiveRenderer.h"

class PixelRecursorApp {
public:
    PixelRecursorApp() : running(true), window(nullptr), renderer(nullptr) {}
    
    bool initialize() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }
        
        window = SDL_CreateWindow("PixelRecursor - Recursive Pixel Art Editor",
                                 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        
        if (!window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }
        
        // Initialize components
        editor = std::make_unique<PixelEditor>(8);
        palette = std::make_unique<Palette>();
        recursiveRenderer = std::make_unique<RecursiveRenderer>(8, 64);
        
        return true;
    }
    
    void handleEvents() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    
                    // Check if click is on palette
                    if (palette->handleClick(mouseX, mouseY, PALETTE_X, PALETTE_Y, PALETTE_CELL_SIZE)) {
                        // Palette selection handled
                    }
                    // Check if click is on editor grid
                    else if (editor->handleClick(mouseX, mouseY, EDITOR_X, EDITOR_Y, 
                                               EDITOR_CELL_SIZE, palette->getCurrentColorIndex())) {
                        // Pixel edited
                    }
                }
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_c) {
                    editor->clear();
                }
            }
        }
    }
    
    void render() {
        // Clear screen with dark background
        SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
        SDL_RenderClear(renderer);
        
        // Render editor grid with actual colors
        renderEditorGrid();
        
        // Render palette
        palette->render(renderer, PALETTE_X, PALETTE_Y, PALETTE_CELL_SIZE);
        
        // Render recursive output
        recursiveRenderer->render(renderer, *editor, *palette, RECURSIVE_X, RECURSIVE_Y);
        
        // Render UI text (simple rectangles as placeholders)
        renderUI();
        
        SDL_RenderPresent(renderer);
    }
    
    void renderEditorGrid() {
        const auto& pixelData = editor->getPixelData();
        
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                SDL_Rect rect = {
                    EDITOR_X + x * EDITOR_CELL_SIZE,
                    EDITOR_Y + y * EDITOR_CELL_SIZE,
                    EDITOR_CELL_SIZE,
                    EDITOR_CELL_SIZE
                };
                
                // Fill with pixel color
                int colorIndex = pixelData[y][x];
                SDL_Color color = palette->getColor(colorIndex);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &rect);
                
                // Draw grid lines
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
    
    void renderUI() {
        // Draw labels as simple rectangles (in a real app, you'd use text rendering)
        SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
        
        // Editor label
        SDL_Rect editorLabel = {EDITOR_X, EDITOR_Y - 25, 100, 20};
        SDL_RenderFillRect(renderer, &editorLabel);
        
        // Palette label
        SDL_Rect paletteLabel = {PALETTE_X, PALETTE_Y - 25, 80, 20};
        SDL_RenderFillRect(renderer, &paletteLabel);
        
        // Recursive output label
        SDL_Rect recursiveLabel = {RECURSIVE_X, RECURSIVE_Y - 25, 120, 20};
        SDL_RenderFillRect(renderer, &recursiveLabel);
    }
    
    void update() {
        handleEvents();
        render();
    }
    
    bool isRunning() const { return running; }
    
    void cleanup() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    }

private:
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    static const int EDITOR_CELL_SIZE = 40;
    static const int PALETTE_CELL_SIZE = 30;
    static const int EDITOR_X = 50;
    static const int EDITOR_Y = 80;
    static const int PALETTE_X = 50;
    static const int PALETTE_Y = 450;
    static const int RECURSIVE_X = 400;
    static const int RECURSIVE_Y = 80;
    
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    std::unique_ptr<PixelEditor> editor;
    std::unique_ptr<Palette> palette;
    std::unique_ptr<RecursiveRenderer> recursiveRenderer;
};

// Global app instance for Emscripten
PixelRecursorApp* g_app = nullptr;

void mainLoop() {
    if (g_app && g_app->isRunning()) {
        g_app->update();
    }
#ifdef __EMSCRIPTEN__
    else {
        emscripten_cancel_main_loop();
    }
#endif
}

int main() {
    g_app = new PixelRecursorApp();
    
    if (!g_app->initialize()) {
        std::cerr << "Failed to initialize application!" << std::endl;
        delete g_app;
        return -1;
    }
    
#ifdef __EMSCRIPTEN__
    // Set up main loop for Emscripten
    emscripten_set_main_loop(mainLoop, 60, 1);
#else
    // Native main loop
    while (g_app->isRunning()) {
        g_app->update();
        SDL_Delay(16); // ~60 FPS
    }
#endif
    
    g_app->cleanup();
    delete g_app;
    
    return 0;
}
