#include "screen.h"

#include <iostream>

Screen::Screen(const char* title, int width, int height) :
    title_(title), width_(width), height_(height) {
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
}

Screen::~Screen() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Screen::clear() {
    SDL_SetRenderDrawColor(renderer_,255,255,255,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);
}

void Screen::render() {
    SDL_RenderPresent(renderer_);
}