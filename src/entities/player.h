#ifndef SRC_ENTITIES_PLAYER_H
#define SRC_ENTITIES_PLAYER_H

#include "graphics/board.h"
#include "utils/constants.h"

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

    bool is_valid(int row, int col);

    bool is_active_{false};
};

#endif // SRC_ENTITIES_PLAYER_H