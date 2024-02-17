#include "../inc/Player.hpp"

void Player::draw(){
    texture.render(&frames.at(0),&cur_pos);
}

void Player::move(int x, int y){
    cur_pos.x +=x;
}

void Player::redraw(){
    draw();
}