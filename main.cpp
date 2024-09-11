#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <tuple>
#include "circle.h"
#include <SDL2/SDL.h>

// Game objects:
// Tile: includes position data on window along with marker that occupies it
// Marker: composed of a color and x, y, r position/dimensions
// Player: contains info about current score, the configured Marker color, and a vector of pointers to Tiles that the player owns
// Game: manages current state of game, including initialization, rending, and updating objects

// Coordinate system: x-axis is pointing right and y-axis is pointing down

namespace {
    constexpr int kGridWidth = 400;
    constexpr int kGridHeight = 400;

    constexpr int kWindowWidth = 640;
    constexpr int kWindowHeight = 480;

    constexpr int num_tiles = 64;

    const int rows = std::sqrt(num_tiles);
    const int cols = std::sqrt(num_tiles);
}

enum class Color {
    NONE,
    BLACK,
    WHITE,
};

bool IsOnBoard(int x, int y) {
    // board boundaries
    int upperLeftX = (kWindowWidth - kGridWidth)/2;
    int upperLeftY = (kWindowHeight - kGridHeight)/2;
    int bottomRightX = upperLeftX + kGridWidth;
    int bottomRightY = upperLeftY + kGridHeight;

    if (x < upperLeftX || x > bottomRightX) {
        return false;
    }
    else if (y < upperLeftY || y > bottomRightY) {
        return false;
    }
    else {
        return true;
    }
}

// convert a (x,y) position of a tile into a linear index
int TileXYToIndex(int x, int y) {
    return (y * cols + x);
}

// convert a linear index into (x,y) position of a tile
std::tuple<int, int> IndexToTileXY(int index) {
    int x = index % rows;
    int y = index / rows;
    return std::make_tuple(x, y);
}

struct Marker {
    int _x;
    int _y;
    int radius{10};
    Color _color{Color::NONE};

    std::array<int, 3> rgb{0,0,0};

    void SetColor(Color color) {
        if (color == Color::BLACK) {
            rgb = {0,0,0};
        }
        else if (color == Color::WHITE) {
            rgb = {255,255,255};
        }
        else {
            rgb = {1,50,32};
        }
        _color = color;
    }

    Color GetColor() {
        return _color;
    }

    void SetPosition(int x, int y) {
        _x = x;
        _y = y;
    }

    void Render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer,rgb[0], rgb[1], rgb[2], SDL_ALPHA_OPAQUE);
        SDL_RenderFillCircle(renderer, _x, _y, radius);
    }
};

struct Tile {
    int _x;
    int _y;
    int _w;
    int _h;
    Marker _marker;

    void Initialize(int x, int y, int w, int h) {
        _x = x;
        _y = y;
        _w = w;
        _h = h;
        
        // Initialize tile with empty marker
        _marker.SetColor(Color::NONE);
        _marker.SetPosition(_x+w/2.0, _y+_h/2.0);
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
        _marker.Render(renderer);
    }
};

struct Player {
    std::vector<Tile*> tiles{};
    int score{0};
    Color _color{Color::NONE};

    void Initialize(std::array<Tile, num_tiles>& board, Color color) {
        score = 2;
        _color = color;
        int index = 0;
        if (color == Color::BLACK) {
            index = TileXYToIndex(4, 3);
            tiles.push_back(&board[index]);
            index = TileXYToIndex(3,4);
            tiles.push_back(&board[index]);
            tiles[0]->_marker.SetColor(color);
            tiles[1]->_marker.SetColor(color);
        }
        else if (color == Color::WHITE) {
            index = TileXYToIndex(3, 3);
            tiles.push_back(&board[index]);
            index = TileXYToIndex(4,4);
            tiles.push_back(&board[index]);
            tiles[0]->_marker.SetColor(color);
            tiles[1]->_marker.SetColor(color);
        }
    }

    bool IsValidMove(std::array<Tile, num_tiles>& board, int x, int y) {
        int index = TileXYToIndex(x, y);
        Color tile_color = board[index]._marker.GetColor();
        if(tile_color != Color::NONE) {
            return false;
        }
        return true;
    }

    // checks if a given input tile is a valid move
    // sets marker color of this tile
    // updates surrounding neighbors to player color
    // updates score
    // (x,y) are tile coordinates of where to place marker
    // returns true if move was made successfully, false otherwise
    bool MakeMove(std::array<Tile, num_tiles>& board, int x, int y) {
        bool is_valid = IsValidMove(board, x, y);
        
        if(is_valid) {
            int index = TileXYToIndex(x, y);
            tiles.push_back(&board[index]);
            tiles.back()->_marker.SetColor(_color);
        }
        return is_valid;
    }

    void PrintTiles() {
        std::cout << "Printing tiles" << std::endl;
        for(int i = 0; i < tiles.size(); i++) {
            std::cout << "Tile " << i << ": " << tiles[i] << std::endl;
        }
    }

    void Reset(std::array<Tile, num_tiles>& board) {
        for(int i = 0; i < tiles.size(); i++) {
            tiles[i]->_marker.SetColor(Color::NONE);
        }
        tiles.clear();
        Initialize(board, _color);
        
    }
};

struct Game {
    std::array<Tile, num_tiles> _board;
    Player _p1;
    Player _p2;
    int player_index{0};
    std::array<Player, 2> players;


    void Initialize() {
        int x = (kWindowWidth - kGridWidth)/2;
        int y = (kWindowHeight - kGridHeight)/2;

        int w = kGridWidth / rows;
        int h = kGridHeight / cols;
        
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                int index = i*cols + j;
                _board[index].Initialize(x + j*w, y + i*h, w, h);
            }
        }
        players[0].Initialize(_board, Color::BLACK);
        players[1].Initialize(_board, Color::WHITE);
    }

    // Convert a pixel coordinate (x, y) into an (x, y) position of a tile
    // If pixel coordinate does not fall on any tile, return (-1, -1)
    std::tuple<int, int> WindowXYToTileXY(int x, int y) {
        int tileX{0};
        int tileY{0};
        if(!IsOnBoard(x, y)) {
            tileX = -1, tileY = -1;
            return std::make_tuple(tileX, tileY);
        }
        int upperLeftX = (kWindowWidth - kGridWidth)/2;
        int upperLeftY = (kWindowHeight - kGridHeight)/2;
        int shiftedX = x - upperLeftX;
        int shiftedY = y - upperLeftY;
        int tileW = kGridWidth / rows;
        int tileH = kGridHeight / cols;

        tileX = shiftedX / tileH;
        tileY = shiftedY / tileW;
        return std::make_tuple(tileX, tileY);
    }

    // @param x: x coordinate of mouse button press
    // @param y: y coordinate of mouse button press
    void Update(int x, int y) {
        std::cout << "x = " << x << ", y = " << y << std::endl;
        std::cout << "IsOnBoard = " << IsOnBoard(x, y) << std::endl;
        auto [tileX, tileY] = WindowXYToTileXY(x, y);
        std::cout << "tileX = " << tileX << ", tileY = " << tileY << std::endl;
        if(IsOnBoard(x, y)) {
            bool result = players[player_index].MakeMove(_board, tileX, tileY);
            if (result) {
                player_index = (player_index + 1) % 2;
            }
        }
        players[0].PrintTiles();
        players[1].PrintTiles();
    }

    void ClearBoard() {
        std::cout << "Clearing board!" << std::endl;
        players[0].Reset(_board);
        players[1].Reset(_board);
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
            _board[i].Render(renderer);
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

    // Player p1;
    // p1.Initialize(game._board, Color::BLACK);

    // Player p2;
    // p2.Initialize(game._board, Color::WHITE);

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
            if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_C) {
                game.ClearBoard();
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