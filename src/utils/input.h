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

    private:
        SDL_Event event_;

        bool quit_{false};
    
};

#endif // SRC_UTILS_INPUT_H