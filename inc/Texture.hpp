#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture {
    
    SDL_Texture* texture;
    SDL_Renderer* renderer;

    public:

    Texture(std::string path, SDL_Renderer* renderer);

    Texture(const char* path, SDL_Renderer* renderer);

    void render(SDL_Rect* clip, SDL_Rect* canvas);
    
    SDL_Renderer* get_renderer() {return renderer;}
    
};

#endif