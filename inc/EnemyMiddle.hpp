#ifndef _ENEMYMIDDLE_HPP_
#define _ENEMYMIDDLE_HPP_

#include "Enemy.hpp"

class EnemyMiddle : public Enemy {
    public:
    EnemyMiddle(Texture& texture, SDL_Rect pos, int hp):Enemy(texture,pos,hp){
        cur_pos.w = enemy_width;
        cur_pos.h = enemy_height;
        frames.push_back((SDL_Rect){0,9,8,8});
        frames.push_back((SDL_Rect){9,9,8,8});
    }
};

#endif