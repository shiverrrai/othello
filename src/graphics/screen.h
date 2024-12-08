#ifndef SRC_GRAPHICS_SCREEN_H
#define SRC_GRAPHICS_SCREEN_H

#include <SDL2/SDL.h>
#include "board.h"

/// @class Screen class manages windowing and screen graphics
class Screen {
    public:
        Screen(const char* title, int width, int height, Board& board);

        ~Screen();

        void clear();

        void render();

    private:
        SDL_Window* window_{nullptr};
        SDL_Renderer* renderer_{nullptr};
        Board& board_;

        void initialize_board();

        const char* title_;
        int width_, height_;
};

#endif // SRC_GRAPHICS_SCREEN_H