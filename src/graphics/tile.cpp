#include "tile.h"
#include "circle.h"

void Tile::initialize(const Point& origin, int length) {
    origin_ = origin;
    length_ = length;
}

void Tile::render(SDL_Renderer* renderer) {
    SDL_Rect rectangle {
        origin_.x,
        origin_.y,
        length_,
        length_,
    };
    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rectangle);
    switch (color_)
    {
    case constants::Color::NONE:
        SDL_SetRenderDrawColor(renderer,1,50,32,SDL_ALPHA_OPAQUE);
        break;
    case constants::Color::BLACK:
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        break;
    case constants::Color::WHITE:
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    default:
        break;
    }
    double radius = 0.6*(length_/2.0);
    SDL_RenderFillCircle(renderer, origin_.x + length_/2.0, origin_.y + length_/2.0, radius);
}

void Tile::set_color(constants::Color color) {
    color_ = color;
}

bool Tile::is_empty() {
    return color_ == constants::Color::NONE;
}