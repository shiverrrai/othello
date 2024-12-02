#include "input.h"

void Input::update() {
    while(SDL_PollEvent(&event_)){
        if(event_.type == SDL_QUIT){
            quit_ = true;
        }
    }
}