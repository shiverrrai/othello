#ifndef SRC_UTILS_INPUT_H
#define SRC_UTILS_INPUT_H

#include <SDL2/SDL.h>

/// @class Input class represents and manages any user 
/// input that may update the state of the game
class Input {
    public:
        Input() = default;

        /// @brief polls for user-generated events and updates 
        /// state variables accordingly
        void update();

        inline bool is_window_closed() const {
            return quit_;
        }

        bool get_mouse_press(int& mouse_press_x, int& mouse_press_y);

    private:
        SDL_Event event_;

        int mouse_press_x_, mouse_press_y_;

        bool quit_{false};
        bool is_mouse_pressed_{false};
    
};

#endif // SRC_UTILS_INPUT_H