#ifndef SRC_GAME_H
#define SRC_GAME_H

#include "graphics/screen.h"
#include "utils/input.h"

class Game {
    public:
        Game(const char* title, int width, int height);

        void update();
        void render();

        bool is_running() const;
    
    private:
        Input input_{};
        Screen screen_;
};

#endif // SRC_GAME_H