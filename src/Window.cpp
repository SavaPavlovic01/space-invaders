#include "../inc/Window.hpp"
#include "../inc/EnemyFront.hpp"
#include "../inc/Enemy.hpp"
#include <iostream>
#include "../inc/EnemyBack.hpp"
#include "../inc/EnemyMiddle.hpp"


void Window::init(){
    window = SDL_CreateWindow(window_name.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    tick_cnt = SDL_GetTicks();
    init_game();
}

Window::~Window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int Window::get_event(SDL_Event& event){
    return SDL_PollEvent(&event);
}

void Window::handle_event(SDL_Event& event){
    switch (event.type)
    {
        case SDL_QUIT:
            handle_quit(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            handle_mouse(event); 
            break;
        case SDL_KEYDOWN:
            handle_keyboard(event);
            break;
        default:
            break;
    }
}

void Window::handle_quit(SDL_Event& event){
    quit = true;
}

void Window::handle_mouse(SDL_Event& event){

}

void Window::handle_keyboard(SDL_Event& event){
    
}

void Window::loop(){
    SDL_Event event;
    tick_cnt = SDL_GetTicks();
    while(!quit){
        if(get_event(event))
            handle_event(event);
        if(SDL_GetTicks()-tick_cnt>400){
            tick_cnt = SDL_GetTicks();
            for(auto entity:enemys){
                entity->draw();
            }
            draw_scene();            
            update_scene();
        }
    }
}


void Window::draw_scene(){
    SDL_RenderPresent(get_renderer());
    SDL_RenderClear(get_renderer());
}

void Window::init_game(){
    sprite_sheet = new Texture("images/sheet.png",get_renderer());
    SDL_Rect pos = {5,5,32,32};
    for(int i = 0; i<11;i++){
        for(int j = 0;j<5;j++){
            Entity* cur_entity = nullptr; 
            if(j == 0) cur_entity = new EnemyBack(*sprite_sheet, pos, 1);
            else if(j>=3) cur_entity = new EnemyFront(*sprite_sheet, pos, 1);   
            else cur_entity = new EnemyMiddle(*sprite_sheet, pos,1);
            pos.y +=enemy_y_distance;
            enemys.push_back(cur_entity);
        }
        pos.x += enemy_x_distance;
        pos.y = 5;
    }

}

void Window::update_scene(){
    bool going_down = false;
    Entity* last_enemy = (cur_direction == 1)? enemys.at(enemys.size()-1):enemys.at(0);
    int check =last_enemy->get_x()+ enemy_movment_per_frame*cur_direction;
    check = (cur_direction == 1)? check+last_enemy->get_w():check;
    if(check>= width && cur_direction == 1){
        going_down = true;
        cur_direction *= -1;
    }else if(check <=0 && cur_direction == -1){
        going_down = true;
        cur_direction *= -1;
    }
    int offsetX = (going_down)? 0:enemy_movment_per_frame*cur_direction;
    int offsetY = (going_down)? 32:0;
    for(auto entity: enemys){
        entity->move(offsetX,offsetY);
    }
}