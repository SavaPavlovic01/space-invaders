#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

#include "Wall.hpp"

class Square : public Wall{

    public:

    Square(Texture& texture, SDL_Rect pos, int hp): Wall(texture,pos,hp){
        frames.push_back((SDL_Rect){173,126,8,8});
        frames.push_back((SDL_Rect){164,126,8,8});
        frames.push_back((SDL_Rect){155,126,8,8});
        frames.push_back((SDL_Rect){146,126,8,8});
        frames.push_back((SDL_Rect){137,126,8,8});
    }

};

#endif