#include "../inc/Wall.hpp"

void Wall::draw(){
    texture.render(&frames.at(hp-1),&cur_pos);
}

void Wall::redraw(){
    draw();
}

bool Wall::shoot(){
    return false;
}

void Wall::move(int x, int y){
    return;
}