#include "../inc/Entity.hpp"
#include <iostream>

Entity::Entity(Texture& texture, SDL_Rect pos):texture(texture) {
    cur_pos = pos;
}


