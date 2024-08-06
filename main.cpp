#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>

namespace {
    constexpr int kGridWidth = 400;
    constexpr int kGridHeight = 400;

    constexpr int kWindowWidth = 640;
    constexpr int kWindowHeight = 480;

    constexpr int num_tiles = 64;
}

struct Marker {
    int _r;
    int _g;
    int _b;

    int x;
    int y;
    int radius;

    void SetColor(int r, int g, int b) {
        _r = r;
        _g = g;
        _b = b;
    }

    void Render();
};

struct Tile {
    int _x;
    int _y;
    int _w;
    int _h;
    Marker* marker{nullptr};

    void Initialize(int x, int y, int w, int h) {
        _x = x;
        _y = y;
        _w = w;
        _h = h;
    }

    void Render(SDL_Renderer* renderer) {
        SDL_Rect rectangle {
            _x,
            _y,
            _w,
            _h,
        };
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &rectangle);
    }
};

struct Player {
    std::vector<Tile> tiles{};
    int score{0};
};

struct Game {
    std::array<Tile, num_tiles> board;
    Player p0;
    Player p1;

    void Initialize() {
        int rows = std::sqrt(num_tiles);
        int cols = std::sqrt(num_tiles);

        int x = (kWindowWidth - kGridWidth)/2;
        int y = (kWindowHeight - kGridHeight)/2;

        int w = kGridWidth / rows;
        int h = kGridHeight / cols;
        
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                int index = i*cols + j;
                board[index].Initialize(x + j*w, y + i*h, w, h);
            }
        }
    }

    // @param x: x coordinate of mouse button press
    // @param y: y coordinate of mouse button press
    void Update(int x, int y) {
        std::cout << "x = " << x << ", y = " << y << std::endl;
    }

    void Render(SDL_Renderer* renderer) {
        int x = (kWindowWidth - kGridWidth)/2;
        int y = (kWindowHeight - kGridHeight)/2;

        SDL_Rect rectangle {
            x,
            y,
            kGridWidth,
            kGridHeight,
        };
        SDL_SetRenderDrawColor(renderer,1,50,32,SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rectangle);

        for(int i = 0; i < num_tiles; ++i) {
            board[i].Render(renderer);
        }
    }
};

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

    // Initialize game
    Game game;
    game.Initialize();

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
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                game.Update(event.button.x, event.button.y);
            }
        }
        // (2) Handle Updates
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        game.Render(renderer);

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