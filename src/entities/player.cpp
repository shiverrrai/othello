#include "player.h"
#include <iostream>

Player::Player(Board& board, constants::Color color) :
    board_(board), color_(color) {}

bool Player::make_move(int x, int y) {
    if(board_.on_board(x, y)) {
        Point tile = board_.xy_to_tile(x, y);
        if(is_valid(tile.x_, tile.y_)) {
            std::cout << "player's move is valid. setting (" 
                << tile.x_ << ", " << tile.y_ << ") to " 
                << static_cast<int>(color_) << std::endl;
            board_.get_tile(tile.x_, tile.y_).set_color(color_);
            return true;
        }
    }
    return false;
}

bool Player::is_valid(int row, int col) {
    if(board_.get_tile(row, col).get_color() == constants::Color::NONE) {
        return true;
    }
    return false;
}