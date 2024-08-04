#include <iostream>
#include <SDL2/SDL.h>

// DrawGrid(renderer, num_rows, num_cols);
// DrawTile(x, y)

namespace {
    constexpr int kGridWidth = 400;
    constexpr int kGridHeight = 400;

    constexpr int kWindowWidth = 640;
    constexpr int kWindowHeight = 480;
}

void draw_grid(SDL_Renderer* renderer, int rows, int cols) {
    int x = (kWindowWidth - kGridWidth)/2;
    int y = (kWindowHeight - kGridHeight)/2;

    SDL_Rect rectangle {
        x,              // x
        y,              // y
        kGridWidth,     // w
        kGridHeight,    // h
    };

    SDL_SetRenderDrawColor(renderer,1,50,32,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    float tile_width = kGridWidth / rows;
    float tile_height = kGridHeight / cols;
    for(int i = 1; i < rows; ++i) {
        SDL_RenderDrawLine(renderer, x, y + i*tile_height, x+kGridWidth, y+i*tile_height);
    }
    for(int i = 1; i < cols; ++i) {
        SDL_RenderDrawLine(renderer, x+i*tile_width, y, x+i*tile_width, y+kGridHeight);
    }
}

int main() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }

    SDL_Window* window = nullptr; 
    window = SDL_CreateWindow("Othello",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,kWindowWidth,kWindowHeight,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
        }
        // (2) Handle Updates
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Do our drawing
        draw_grid(renderer, 8, 8);

        // Finally show what we've drawn
        SDL_RenderPresent(renderer);
    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // our program.
    SDL_Quit();

    return 0;
}