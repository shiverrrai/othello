#include "board.h"

Board::Board(Point origin, int length) : 
    origin_(origin), length_(length) {}

void Board::render(SDL_Renderer* renderer) {
    SDL_Rect rectangle {
        origin_.x_,
        origin_.y_,
        length_,
        length_,
    };
    SDL_SetRenderDrawColor(renderer,1,50,32,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rectangle);
}

void Board::set_origin(const Point& origin) {
    origin_ = origin;
}

void Board::set_length(int length) {
    length_ = length;
}