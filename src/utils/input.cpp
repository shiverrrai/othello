#include "input.h"

void Input::update() {
    is_mouse_pressed_ = false;
    while(SDL_PollEvent(&event_)){
        switch (event_.type)
        {
        case SDL_QUIT:
            quit_ = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_pressed_ = true;
            if (event_.button.button == SDL_BUTTON_LEFT) {
                mouse_press_x_ = event_.button.x;
                mouse_press_y_ = event_.button.y;
            }
        default:
            break;
        }
    }
}

bool Input::get_mouse_press(int& mouse_press_x, int& mouse_press_y) {
    if(is_mouse_pressed_) {
        mouse_press_x = mouse_press_x_;
        mouse_press_y = mouse_press_y_;
        return true;
    }
    return false;
}