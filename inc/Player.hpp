#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Entity.hpp"

class Player : public Entity{
    int hp = 1;

    public:
    Player(Texture& texture, SDL_Rect pos, int hp = 1):Entity(texture, pos, hp){
        this->hp = hp;
        frames.push_back((SDL_Rect){115,63,11,8});
    }    

    void draw() override;

    void move(int x, int y) override;

    void redraw() override;

    bool shoot() override {return false;}

    bool bullet_hit_player(Entity* bullet);
};

#endif