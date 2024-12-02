#include "game.h"

int main(int argc, const char * argv[]) {
    // Construct game object
    Game game("Othello", 640, 480);

    // Run game loop
    while(game.is_running()) {
        game.update();
        game.render();
    }

    return 0;
}