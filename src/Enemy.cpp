#include "../inc/Enemy.hpp"
#include <iostream>

void Enemy::move(int x, int y) {
    cur_pos.x += x;
    cur_pos.y += y;
}

void Enemy::draw(){
    texture.render(&frames.at(cur_frame++),&cur_pos);
    if(cur_frame == frames.size()) cur_frame = 0;
}

void Enemy::redraw(){
    texture.render(&frames.at((cur_frame ==0)? frames.size()-1: cur_frame-1),&cur_pos);
}