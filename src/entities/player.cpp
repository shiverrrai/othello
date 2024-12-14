#include "player.h"
#include "graphics/point.h"
#include <iostream>

namespace {

std::array<std::pair<int,int>, constants::kRows> kDirections{
    {{-1,-1}, {0,-1}, {1,-1}, {-1, 0}, 
    {1, 0}, {-1, 1}, {0, 1}, {1, 1}}
};

void print_directions(std::vector<std::pair<int,int>>& directions) {
    for (auto direction : directions) {
        std::cout << "{" << direction.first << ", " << direction.second << "}" << std::endl;
    }
}

void print_grid_location(std::pair<int,int>& grid_location){
    std::cout << "(" << grid_location.first << ", " << grid_location.second << ")" << std::endl;
}
}

Player::Player(Board& board, constants::Color color) :
    board_(board), color_(color) {
    opponent_color_ = (color_ == constants::Color::BLACK) ?
        constants::Color::WHITE : constants::Color::BLACK;
}

bool Player::make_move(int x, int y) {
    if(board_.xy_on_board(x, y)) {
        std::pair<int,int> grid_location = board_.xy_to_row_col(x, y);
        std::cout << "xy_to_row_col:" << std::endl;
        print_grid_location(grid_location);
        std::vector<std::pair<int,int>> valid_directions{};
        if(is_valid(grid_location.first, grid_location.second, valid_directions)) {
            std::cout << "printing the valid directions for the given mouse press..." << std::endl;
            print_directions(valid_directions);
            // loop through all valid directions and flip existing tile colors
            flip_tiles(grid_location.first, grid_location.second, valid_directions);
            return true;
        }
    }
    return false;
}

bool Player::is_valid(int row, int col, std::vector<std::pair<int,int>>& valid_directions) {
    if (board_.get_tile(row, col).is_empty()) {
        for (auto direction : kDirections) {
            int flip_count = 0;
            std::pair<int,int> next_tile{row+direction.first, col+direction.second};
            std::cout << "visiting..." << std::endl;
            print_grid_location(next_tile);
            while(can_flip_tile(next_tile.first, next_tile.second)) {
                std::cout << "can flip tile..." << std::endl;
                print_grid_location(next_tile);
                next_tile.first += direction.first;
                next_tile.second += direction.second;
                flip_count++;
            }
            if(flip_count > 0 && 
                board_.get_tile(next_tile.first,next_tile.second).get_color() == color_) {
                valid_directions.push_back(direction);
            }
        }
    } 
    return !valid_directions.empty();
}

void Player::flip_tiles(int row, int col, std::vector<std::pair<int,int>>& directions) {
    // set current tile to Player color
    board_.get_tile(row, col).set_color(color_);
    
    for(auto direction : directions) {
        int next_row = row + direction.first;
        int next_col = col + direction.second;
        Tile& next_tile = board_.get_tile(next_row, next_col);
        if (next_tile.get_color() != color_) {
            next_tile.set_color(color_);
        }
    }
}

bool Player::can_flip_tile(int row, int col) {
    constants::Color color = board_.get_tile(row, col).get_color();
    bool result = (board_.row_col_on_board(row, col) && color == opponent_color_);
    std::cout << "On board = " << board_.row_col_on_board(row, col) << std::endl;
    std::cout << "color == opponents color = " << (color == opponent_color_) << std::endl;
    std::cout << "Can flip = " << result << std::endl;
    return result;
}
