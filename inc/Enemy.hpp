#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include "Entity.hpp"


class Enemy : public Entity{

    protected:

    
    int enemy_width = 32;
    int enemy_height = 32;
    SDL_Rect death_frame = (SDL_Rect){103,0,8,8};

    public:

    Enemy(Texture& texture,SDL_Rect pos, int hp):Entity(texture,pos,hp){

    }

    void move(int x, int y) override;

    void draw() override;

    void redraw() override;
   
    virtual bool shoot() {};

};

#endif