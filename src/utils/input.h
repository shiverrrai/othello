#include <SDL2/SDL.h>

class Input {
    public:
        Input() = default;

        void update();

        inline bool is_window_closed() {
            return quit_;
        }

    private:
        SDL_Event event_;

        bool quit_{false};
    
};