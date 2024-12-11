#include "board.h"

void Board::initialize(const Point& origin, int length) {
    origin_ = origin;
    length_ = length;
    initialize_tiles();
}

void Board::initialize_tiles() {
    int w = length_ / constants::kRows;
    int h = length_ / constants::kCols;

    for(int i = 0; i < constants::kRows; ++i) {
        for(int j = 0; j < constants::kCols; ++j) {
            int index = i*constants::kCols + j;
            tiles_[index].initialize(
                Point{origin_.x_ + j*w, origin_.y_ + i*h}, 
                length_ / constants::kRows);
        }
    }

    // place initial tiles to start game
    tiles_[tile_to_index(Point{3, 3})].set_color(constants::Color::BLACK);
    tiles_[tile_to_index(Point{4, 4})].set_color(constants::Color::BLACK);
    tiles_[tile_to_index(Point{4, 3})].set_color(constants::Color::WHITE);
    tiles_[tile_to_index(Point{3, 4})].set_color(constants::Color::WHITE);
}

void Board::render(SDL_Renderer* renderer) {
    SDL_Rect rectangle {
        origin_.x_,
        origin_.y_,
        length_,
        length_,
    };
    SDL_SetRenderDrawColor(renderer,1,50,32,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rectangle);

    for(int i = 0; i < constants::kNumTiles; ++i) {
        tiles_[i].render(renderer);
    }
}

bool Board::on_board(int x, int y) {
    // board boundaries
    Point bottom_right{origin_.x_ + length_, 
        origin_.y_ + length_ };

    if (x < origin_.x_ || x > bottom_right.x_) {
        return false;
    }
    else if (y < origin_.y_ || y > bottom_right.y_) {
        return false;
    }
    else {
        return true;
    }
}

Tile& Board::get_tile(int row, int col) {
    return tiles_[tile_to_index(Point{row, col})];
}

Point Board::index_to_tile(int index) {
    int x = index % constants::kRows;
    int y = index / constants::kRows;
    return Point{x, y};
}

int Board::tile_to_index(const Point& tile) {
    return (tile.y_ * constants::kCols + tile.x_);
}

Point Board::xy_to_tile(int x, int y) {
    if(!on_board(x, y)) {
        return {-1, -1};
    }
    int x_board = x - origin_.x_;
    int y_board = y - origin_.y_;
    int tile_width = length_ / constants::kRows;
    int tile_height = length_ / constants::kCols;

    Point tile{x_board / tile_width, y_board / tile_height};
    return tile;
}

