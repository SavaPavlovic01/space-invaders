#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include "Texture.hpp"
#include <vector>

class Entity {
    protected:
    Texture& texture;
    std::vector<SDL_Rect> frames;
    uint32_t cur_frame = 0;
    SDL_Rect cur_pos;

    public:

    Entity(Texture& texture, SDL_Rect pos);

    void add_frame(SDL_Rect rect) {frames.push_back(rect);}

    virtual void draw() {};

    virtual void redraw() {};

    virtual void move(int x, int y) {};

    int get_w(){return cur_pos.w;}

    int get_h(){return cur_pos.h;}

    int get_x(){return cur_pos.x;}

    int get_y(){return cur_pos.y;}

};

#endif