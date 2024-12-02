#include <SDL2/SDL.h>

class Screen {
    public:
        Screen(const char* title, int width, int height);

        ~Screen();

        void clear();

        void render();

    private:
        const char* title_;
        const int width_, height_;
        SDL_Window* window_{nullptr};
        SDL_Renderer* renderer_{nullptr};
};