#ifndef SRC_GRAPHICS_BOARD_H
#define SRC_GRAPHICS_BOARD_H

#include <SDL2/SDL.h>
#include <array>
#include <utility>

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
        
        /// @brief convert a 1d index to a (row, col) pair on board
        /// @param index 1d index
        /// @return 2d (row, col) location on board
        static std::pair<int,int> index_to_row_col(int index);

        /// @brief convert a (row, col) pair on board to a 1d index
        /// @param row int representing row on board
        /// @param col int representing col on board
        /// @return 1d index as an int
        static int row_col_to_index(int row, int col);

        /// @brief given (x,y) in screen frame, compute (row,col) 
        /// location on board
        /// @param x x location in screen frame
        /// @param y location in screen frame
        /// @return (row, col) location on board
        std::pair<int, int> xy_to_row_col(int x, int y);

        /// @brief determines whether an input (x,y) is on board
        /// @param x x-coordinate of input
        /// @param y y-coordinate of input
        /// @return bool depending on whether input (x,y)
        /// is on board
        bool xy_on_board(int x, int y);

        Tile& get_tile(int row, int col);

        bool row_col_on_board(int row, int col);

    private:
        Point origin_{};

        void initialize_tiles();

        std::array<Tile, constants::kNumTiles> tiles_{};
        int length_{};
};

#endif // SRC_GRAPHICS_BOARD_H