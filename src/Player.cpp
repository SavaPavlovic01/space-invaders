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

bool Player::bullet_hit_player(Entity* entity){
    int left1 = this->get_x();
    int right1 = this->get_x() + this->get_w();
    int top1 = this->get_y();
    int bottom1 = top1 + this->get_h();

    int left2 = entity->get_x();
    int right2 = entity->get_x() + entity->get_w();
    int top2 = entity->get_y();
    int bottom2 = entity->get_y() + entity->get_h();

    if(bottom1 <= top2) return false;
    if(top1 >= bottom2) return false;
    if(right1 <= left2) return false;
    if(left1 >= right2) return false;
    if(abs(top1 - bottom2) <= 12) return false;
    return true;
}