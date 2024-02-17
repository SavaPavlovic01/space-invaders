#include "../inc/Texture.hpp"
#include <iostream>

Texture::Texture(std::string path, SDL_Renderer* renderer){
    SDL_Surface* surface = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    this->renderer = renderer;
    SDL_FreeSurface(surface);
}

Texture::Texture(const char* path, SDL_Renderer* renderer){
    SDL_Surface* surface = IMG_Load(path);
    this->renderer = renderer;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!this->renderer){std::cout<<"Asdasdasd"<<std::endl;}
    SDL_FreeSurface(surface);
}


void Texture::render(SDL_Rect* clip, SDL_Rect* canvas){
    if(this->renderer == nullptr){
        std::cout<<"OVDE"<<std::endl;
    }
    SDL_RenderCopy(this->renderer,texture,clip,canvas);
}