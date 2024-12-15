#include "board.h"

void Board::initialize(const Point& origin, int length) {
    origin_ = origin;
    length_ = length;
    initialize_tiles();
}

void Board::initialize_tiles() {
    int w = length_ / constants::kCols;
    int h = length_ / constants::kRows;

    for(int i = 0; i < constants::kRows; ++i) {
        for(int j = 0; j < constants::kCols; ++j) {
            int index = i*constants::kCols + j;
            tiles_[index].initialize(
                Point{origin_.x + j*w, origin_.y + i*h}, 
                length_ / constants::kRows);
        }
    }

    // place initial tiles to start game
    tiles_[row_col_to_index(3, 3)].set_color(constants::Color::BLACK);
    tiles_[row_col_to_index(4, 4)].set_color(constants::Color::BLACK);
    tiles_[row_col_to_index(4, 3)].set_color(constants::Color::WHITE);
    tiles_[row_col_to_index(3, 4)].set_color(constants::Color::WHITE);
}

void Board::render(SDL_Renderer* renderer) {
    SDL_Rect rectangle {
        origin_.x,
        origin_.y,
        length_,
        length_,
    };
    SDL_SetRenderDrawColor(renderer,1,50,32,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rectangle);

    for(int i = 0; i < constants::kNumTiles; ++i) {
        tiles_[i].render(renderer);
    }
}

bool Board::xy_on_board(int x, int y) {
    // board boundaries
    Point bottom_right{origin_.x + length_, 
        origin_.y + length_ };

    if (x < origin_.x || x > bottom_right.x) {
        return false;
    }
    else if (y < origin_.y || y > bottom_right.y) {
        return false;
    }
    else {
        return true;
    }
}

Tile& Board::get_tile(int row, int col) {
    return tiles_[row_col_to_index(row, col)];
}

std::pair<int,int> Board::index_to_row_col(int index) {
    int col = index % constants::kRows;
    int row = index / constants::kRows;
    return std::make_pair(row, col);
}

int Board::row_col_to_index(int row, int col) {
    return (row * constants::kCols + col);
}

std::pair<int,int> Board::xy_to_row_col(int x, int y) {
    if(!xy_on_board(x, y)) {
        return {-1, -1};
    }
    int x_board = x - origin_.x;
    int y_board = y - origin_.y;
    int tile_width = length_ / constants::kCols;
    int tile_height = length_ / constants::kRows;

    return std::make_pair(y_board / tile_height, x_board / tile_width);
}

bool Board::row_col_on_board(int row, int col) {
    return (row >= 0 && row < constants::kRows && col >= 0 && col < constants::kCols);
}
