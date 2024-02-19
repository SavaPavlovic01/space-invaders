#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#include "Entity.hpp"

class Bullet : public Entity {

    public:

    Bullet(Texture& texture, SDL_Rect pos):Entity(texture,pos,1){}


    void draw() override;

    void move(int x, int y) override;

    bool shoot() override {return false;}
};

#endif