#include "game.h"

Game::Game(const char* title, int width, int height) :
    screen_(title, width, height, board_) {}

void Game::update() {
    input_.update();
}

void Game::render() {
    screen_.clear();
    screen_.render();
}

bool Game::is_running() const {
    return !input_.is_window_closed();
}