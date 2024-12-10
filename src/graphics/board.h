#ifndef SRC_GRAPHICS_BOARD_H
#define SRC_GRAPHICS_BOARD_H

#include <SDL2/SDL.h>
#include <array>
#include "point.h"
#include "tile.h"
#include "utils/constants.h"

/// @class Board is a dynamic grid that the user can interact with
/// through mouse presses or specific key strokes
/// A Board object is composed of an 8x8 grid of Tile objects
class Board {
    public:
        Board() = default;

        void initialize(const Point& origin, int length);

        void update();

        void render(SDL_Renderer* renderer);
        
        static Point index_to_point(int index);

        static int point_to_index(const Point& point);

        Point origin() { return origin_; }
        int length() { return length_; }

    private:
        Point origin_{};

        void initialize_tiles();

        std::array<Tile, constants::kNumTiles> tiles_{};
        int length_{};
};

#endif // SRC_GRAPHICS_BOARD_H