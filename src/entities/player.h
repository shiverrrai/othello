#ifndef SRC_ENTITIES_PLAYER_H
#define SRC_ENTITIES_PLAYER_H

#include "graphics/board.h"
#include "utils/constants.h"

#include <vector>

class Player {
public:
    Player(Board& board, constants::Color color);

    /// Responsible for executing Player's move based on 
    /// user input
    /// @return bool based on whether or not the move was 
    /// executed
    bool make_move(int x, int y);

    inline void switch_turn() {
        is_active_ = !is_active_;
    };

    inline bool is_active() const {
        return is_active_;
    }

    void set_turn(bool active) {
        is_active_ = active;
    }

private:
    Board& board_;
    constants::Color color_;
    constants::Color opponent_color_;

    bool is_valid(int row, int col, std::vector<Point>& valid_directions);

    /// @brief flips tiles from opponent's color to Player color for all directions
    /// @param row row of current tile
    /// @param col column of current tile
    /// @param directions a collection of direction vectors which need their tiles flipped
    void flip_tiles(int row, int col, std::vector<Point>& directions);

    bool is_active_{false};
};

#endif // SRC_ENTITIES_PLAYER_H