#include "player.h"
#include "graphics/point.h"
#include <iostream>

namespace {

std::array<Point, constants::kRows> kDirections{
    {{-1,-1}, {0,-1}, {1,-1}, {-1, 0}, 
    {1, 0}, {-1, 1}, {0, 1}, {1, 1}}
};

void print_directions(std::vector<Point>& directions) {
    for (auto direction : directions) {
        std::cout << "{" << direction.x_ << ", " << direction.y_ << "}" << std::endl;
    }
}

}

Player::Player(Board& board, constants::Color color) :
    board_(board), color_(color) {
    opponent_color_ = (color_ == constants::Color::BLACK) ?
        constants::Color::WHITE : constants::Color::BLACK;
}

bool Player::make_move(int x, int y) {
    if(board_.on_board(x, y)) {
        Point tile = board_.xy_to_tile(x, y);
        std::vector<Point> valid_directions{};
        if(is_valid(tile.x_, tile.y_, valid_directions)) {
            print_directions(valid_directions);
            // loop through all valid directions and flip existing tile colors
            flip_tiles(tile.x_, tile.y_, valid_directions);
            return true;
        }
    }
    return false;
}

bool Player::is_valid(int row, int col, std::vector<Point>& valid_directions) {
    if (board_.get_tile(row, col).is_empty()) {
        for (auto direction : kDirections) {
            Point next_tile{row, col};
            do {
                next_tile.x_ += direction.x_;
                next_tile.y_ += direction.y_;
            } while(board_.in_bounds(next_tile.x_, next_tile.y_) &&
                board_.get_tile(next_tile.x_, next_tile.y_).get_color() == opponent_color_);

            if(board_.get_tile(next_tile.x_, next_tile.y_).get_color() == color_) {
                valid_directions.push_back(direction);
            }
        }
    } 
    return !valid_directions.empty();
}

void Player::flip_tiles(int row, int col, std::vector<Point>& directions) {
    // set current tile to Player color
    board_.get_tile(row, col).set_color(color_);
    
    for(auto direction : directions) {
        int next_row = row + direction.x_;
        int next_col = col + direction.y_;
        Tile& next_tile = board_.get_tile(next_row, next_col);
        if (next_tile.get_color() != color_) {
            next_tile.set_color(color_);
        }
    }
}

