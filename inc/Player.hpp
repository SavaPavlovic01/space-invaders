#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Entity.hpp"

class Player : public Entity{
    int hp = 1;

    public:
    Player(Texture& texture, SDL_Rect pos, int hp = 1):Entity(texture, pos){
        this->hp = hp;
        frames.push_back((SDL_Rect){112,63,16,8});
    }    

    void draw() override;

    void move(int x, int y) override;

    void redraw() override;
};

#endif