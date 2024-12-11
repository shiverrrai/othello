#ifndef SRC_UTILS_CONSTANTS_H
#define SRC_UTILS_CONSTANTS_H

#include <cmath>

namespace constants {

constexpr int kNumTiles = 64;
const int kRows = std::sqrt(kNumTiles);
const int kCols = std::sqrt(kNumTiles);

enum class Color {
    NONE,
    BLACK,
    WHITE
};

}

#endif // SRC_UTILS_CONSTANTS_H