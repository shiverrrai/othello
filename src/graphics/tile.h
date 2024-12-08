#ifndef SRC_GRAPHICS_TILE_H
#define SRC_GRAPHICS_TILE_H

#include <SDL2/SDL.h>
#include "point.h"

/// @class Tile class represents the individual element of a Board
/// that can be accumulated by a Player instance. Each Tile contains 
/// a marker of a specific color, depending on which player owns the Tile
class Tile {
    public:
        Tile() = default;
        
        void initialize(const Point& origin, int length);

        void render(SDL_Renderer* renderer);

    private:
        Point origin_{};

        int length_{};

};

#endif // SRC_GRAPHICS_TILE_H