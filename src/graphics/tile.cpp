#include "tile.h"

void Tile::initialize(const Point& origin, int length) {
    origin_ = origin;
    length_ = length;
}

void Tile::render(SDL_Renderer* renderer) {
    SDL_Rect rectangle {
        origin_.x_,
        origin_.y_,
        length_,
        length_,
    };
    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rectangle);
}