#include "screen.h"

#include <iostream>
#include <algorithm>
#include "point.h"

Screen::Screen(const char* title, int width, int height, Board& board) :
    title_(title), width_(width), height_(height), board_(board) {
    
    window_ = SDL_CreateWindow(
        title_,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width_,
        height_,
        SDL_WINDOW_SHOWN
    );

    if(!window_) {
        throw std::runtime_error("Could not create SDL window!");
    }

    renderer_ = SDL_CreateRenderer(window_,-1,SDL_RENDERER_ACCELERATED);

    initialize_board();
}

Screen::~Screen() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Screen::initialize_board() {
    // compute board length
    const double aspect_ratio = 0.7;
    const int length = static_cast<int>(std::min(width_, height_) * aspect_ratio);
    
    // compute board origin
    const int x = (width_ - length) / 2;
    const int y = (height_ - length) / 2;

    // initialize board
    board_.initialize(Point{x, y}, length);
}

void Screen::clear() {
    SDL_SetRenderDrawColor(renderer_,255,255,255,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);
}

void Screen::render() {
    board_.render(renderer_);
    SDL_RenderPresent(renderer_);
}
