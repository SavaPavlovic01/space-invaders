#ifndef _ENEMYBACK_HPP_
#define _ENEMYBACK_HPP_
#include "Enemy.hpp"
#include "Bullet.hpp"
#include <time.h>

class EnemyBack : public Enemy {

    int shoot_prob = 0;

    static int seed;

    public:
    EnemyBack(Texture& texture,SDL_Rect pos, int hp):Enemy(texture,pos,hp){
        cur_pos.w = enemy_width;
        cur_pos.h = enemy_height;
        frames.push_back((SDL_Rect){0,18,8,8});
        frames.push_back((SDL_Rect){9,18,8,8});
    }
    
    bool shoot() override {
        int num = rand() % 100;
        return num <= shoot_prob;
    }

};  

#endif