#include "graphics/screen.h"
#include "utils/input.h"

class Game {
    public:
        Game(const char* title, int width, int height);

        void update();
        void render();

        bool is_running();
    
    private:
        Input input_{};
        Screen screen_;
};