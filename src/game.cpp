#include "game.h"

Game::Game(const char* title, int width, int height) :
    screen_(title, width, height, board_) {}

void Game::update() {
    input_.update();
    int mouse_press_x, mouse_press_y;
    input_.get_mouse_press(mouse_press_x, mouse_press_y);
}

void Game::render() {
    screen_.clear();
    screen_.render();
}

bool Game::is_running() const {
    return !input_.is_window_closed();
}