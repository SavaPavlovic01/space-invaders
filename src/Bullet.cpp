#include "../inc/Bullet.hpp"

void Bullet::draw(){
    SDL_SetRenderDrawColor(texture.get_renderer(),0xff,0xff,0xff,0xff);
    SDL_RenderFillRect(texture.get_renderer(),&cur_pos);
    SDL_SetRenderDrawColor(texture.get_renderer(),0x00,0x00,0x00,0xff);
}


void Bullet::move(int x, int y){
    cur_pos.y += y;
}