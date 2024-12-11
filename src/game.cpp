#include "game.h"
#include "utils/constants.h"
#include <iostream>

Game::Game(const char* title, int width, int height) :
    screen_(title, width, height, board_),
    player1_(board_, constants::Color::BLACK),
    player2_(board_, constants::Color::WHITE) {
    
    // for now, set player 1 to go first
    player1_.set_turn(true);
    player2_.set_turn(false);
}

void Game::update() {
    input_.update();
    int mouse_press_x, mouse_press_y;
    if (input_.get_mouse_press(mouse_press_x, mouse_press_y)) {
        bool result{false};
        if (player1_.is_active()) {
            std::cout << "Making player 1's turn!" << std::endl;
            result = player1_.make_move(
                mouse_press_x, mouse_press_y);
        }
        else if (player2_.is_active()) {
            std::cout << "Making player 2's turn!" << std::endl;
            result = player2_.make_move(
                mouse_press_x, mouse_press_y);
        }
        if (result) { 
            player1_.switch_turn();
            player2_.switch_turn();
        }
    }
    
}

void Game::render() {
    screen_.clear();
    screen_.render();
}

bool Game::is_running() const {
    return !input_.is_window_closed();
}