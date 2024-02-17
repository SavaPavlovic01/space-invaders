#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include "Entity.hpp"


class Enemy : public Entity{

    protected:

    uint8_t hp=1;
    int enemy_width = 32;
    int enemy_height = 32;

    public:

    Enemy(Texture& texture,SDL_Rect pos, int hp):Entity(texture,pos){
        this->hp = hp;
    }

    void move(int x, int y) override;

    void draw() override;

    void redraw() override;

};

#endif