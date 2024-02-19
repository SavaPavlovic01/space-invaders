#ifndef _WALL_HPP_
#define _WALL_HPP_

#include "Entity.hpp"

class Wall : public Entity{
    public:

    Wall(Texture& texture, SDL_Rect pos, int hp): Entity(texture,pos,hp){

    }

    void draw() override;

    void redraw() override;

    void move(int x, int y) override;

    bool shoot() override;
};

#endif
