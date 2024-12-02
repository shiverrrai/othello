#ifndef SRC_GRAPHICS_BOARD_H
#define SRC_GRAPHICS_BOARD_H

#include <SDL2/SDL.h>
#include "point.h"

class Board {
    public:
        Board() = default;
        Board(Point origin, int length);

        void update();

        void render(SDL_Renderer* renderer);

        void set_origin(const Point& origin);

        void set_length(int length);
    
    private:
        Point origin_{};

        int length_{};
};

#endif // SRC_GRAPHICS_BOARD_H