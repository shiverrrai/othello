#ifndef SRC_GAME_H
#define SRC_GAME_H

#include "graphics/screen.h"
#include "utils/input.h"
#include "entities/player.h"

/// @class Game class holds all components of game along 
/// with functions to render and update the state of the game 
class Game {
    public:
        Game(const char* title, int width, int height);

        /// @brief updates state of game
        void update();

        /// @brief renders game graphics
        void render();

        /// @brief returns whether or not game is running
        /// @return true or false
        bool is_running() const;
    
    private:
        Board board_{};
        Input input_{};
        Screen screen_;
        Player player1_;
        Player player2_;
};

#endif // SRC_GAME_H