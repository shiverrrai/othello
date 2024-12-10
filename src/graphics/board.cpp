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
    tiles_[point_to_index(Point{3, 3})].set_color(constants::Color::BLACK);
    tiles_[point_to_index(Point{4, 4})].set_color(constants::Color::BLACK);
    tiles_[point_to_index(Point{4, 3})].set_color(constants::Color::WHITE);
    tiles_[point_to_index(Point{3, 4})].set_color(constants::Color::WHITE);
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

Point Board::index_to_point(int index) {
    int x = index % constants::kRows;
    int y = index / constants::kRows;
    return Point{x, y};
}

int Board::point_to_index(const Point& point) {
    return (point.y_ * constants::kCols + point.x_);
}

