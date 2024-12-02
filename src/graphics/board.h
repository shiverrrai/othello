#ifndef SRC_GRAPHICS_BOARD_H
#define SRC_GRAPHICS_BOARD_H

#include <SDL2/SDL.h>
#include <array>
#include <cmath>
#include "point.h"
#include "tile.h"

namespace internal {
    constexpr int kNumTiles = 64;

    const int kRows = std::sqrt(kNumTiles);
    const int kCols = std::sqrt(kNumTiles);
}

class Board {
    public:
        Board() = default;

        void initialize(const Point& origin, int length);

        void update();

        void render(SDL_Renderer* renderer);

        
    
    private:
        Point origin_{};

        void initialize_tiles();

        std::array<Tile, internal::kNumTiles> tiles_{};
        int length_{};
};

#endif // SRC_GRAPHICS_BOARD_H