#ifndef _ENEMYFRONT_HPP_
#define _ENEMYFRONT_HPP_

#include "Enemy.hpp"

class EnemyFront : public Enemy {
    public:
    EnemyFront(Texture& texture, SDL_Rect pos, int hp):Enemy(texture,pos,hp){
        cur_pos.w = enemy_width;
        cur_pos.h = enemy_height;
        frames.push_back((SDL_Rect){0,0,8,8});
        frames.push_back((SDL_Rect){9,0,8,8});
    }
    
    bool shoot() override {return false;}
};

#endif