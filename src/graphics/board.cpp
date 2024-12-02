#include "board.h"

void Board::initialize(const Point& origin, int length) {
    origin_ = origin;
    length_ = length;
    initialize_tiles();
}

void Board::initialize_tiles() {
    int w = length_ / internal::kRows;
    int h = length_ / internal::kCols;

    for(int i = 0; i < internal::kRows; ++i) {
        for(int j = 0; j < internal::kCols; ++j) {
            int index = i*internal::kCols + j;
            tiles_[index].initialize(
                Point{origin_.x_ + j*w, origin_.y_ + i*h}, 
                length_ / internal::kRows);
        }
    }

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

    for(int i = 0; i < internal::kNumTiles; ++i) {
        tiles_[i].render(renderer);
    }
}

