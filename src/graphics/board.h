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
        
        static Point index_to_tile(int index);

        static int tile_to_index(const Point& tile);

        /// @brief given (x,y) in screen frame, compute (row,col) 
        /// of Tile on board
        /// @param x x coordinate in screen frame
        /// @param y y coordinate in screen frame
        /// @return Point (row, col) of Tile on board
        Point xy_to_tile(int x, int y);

        /// @brief determines whether an input (x,y) is on board
        /// @param x x-coordinate of input
        /// @param y y-coordinate of input
        /// @return bool depending on whether input (x,y)
        /// is on board
        bool on_board(int x, int y);

        Tile& get_tile(int row, int col);

        bool in_bounds(int row, int col);

    private:
        Point origin_{};

        void initialize_tiles();

        std::array<Tile, constants::kNumTiles> tiles_{};
        int length_{};
};

#endif // SRC_GRAPHICS_BOARD_H