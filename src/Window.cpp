#include "../inc/Window.hpp"
#include "../inc/EnemyFront.hpp"
#include "../inc/Enemy.hpp"
#include <iostream>
#include "../inc/EnemyBack.hpp"
#include "../inc/EnemyMiddle.hpp"
#include <time.h>


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
    //std::cout<<"CLICK"<<std::endl;
    if(player_bullet != nullptr) return;
    SDL_Rect bullet_pos = {0,0,0,0};
    bullet_pos.x = player->get_x() + player->get_w()/2;
    bullet_pos.y = player->get_y() - 8;
    bullet_pos.w = bullet_width;
    bullet_pos.h = bullet_height;
    player_bullet = new Bullet(*sprite_sheet,bullet_pos);
}

void Window::handle_keyboard(SDL_Event& event){
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
        if(paused || game_over) return;
        if(player->get_x() - player_movement <= 0) return;
        player->move(-player_movement,0);
        draw_enemys();
        draw_scene();
        break;
    case SDLK_RIGHT:
        if(paused || game_over) return;
        if(player->get_x() + player_movement + player->get_w() >= width) return;
        player->move(player_movement,0);  
        draw_enemys(); 
        draw_scene();
        break;
    case SDLK_r:
        // MEMORY LEAK
        enemys.clear();
        enemy_bulltets.clear();
        if(player_bullet) {delete player_bullet; player_bullet = nullptr;}
        delete player;
        init_game();
        break;
    case SDLK_p:
        paused = !paused;
        break;
    default:
        break;
    }    
}

void Window::loop(){
    SDL_Event event;
    tick_cnt = 0;

    int bullet_update_tick = 0;
    int move_enemies_tick = 0;
    int enemy_shoot_tick = 0;
    while(!quit){
        if(get_event(event))
            handle_event(event);
        if( paused || game_over) continue;
        //delete dying_enemy;
        //dying_enemy = nullptr;
        if(SDL_GetTicks()-enemy_shoot_tick > 50){
            for(auto shooter:enemys){
                if(shooter->shoot()){
                    int bullet_x = shooter->get_x() + shooter->get_w()/2;
                    int bullet_y = shooter->get_y() + shooter->get_h();
                    int wi = bullet_width;
                    int hi = bullet_height;
                    enemy_bulltets.push_back(new Bullet(*sprite_sheet,(SDL_Rect){bullet_x,bullet_y,wi,hi}));
                }
            }
            enemy_shoot_tick = SDL_GetTicks();
        }
        if(SDL_GetTicks()-bullet_update_tick > 2){
            bool hit = false;
            //enemy bullets
            for(auto bullet:enemy_bulltets){
                if(player->bullet_hit_player(bullet)) game_over = true;
                bullet->move(0,bullet_movement);    
            }
            //player bullet
            if(player_bullet){
                for(auto iterator = enemys.begin();iterator!=enemys.end();iterator++){                    
                    if((*iterator)->bullet_touching(player_bullet)) {
                        if((*iterator)->take_damage()){
                            dying_enemy = (*iterator);
                            enemys.erase(iterator);
                            hit = true;
                            break;
                        }
                        
                    }
                }
                if(player_bullet->get_y() - 10 <=0) {
                    delete player_bullet;
                    player_bullet = nullptr;
                }else player_bullet->move(0,-bullet_movement);
            }
            bullet_update_tick = SDL_GetTicks();
            if(hit) {
                delete player_bullet;
                player_bullet = nullptr;
            }
        }
        if(SDL_GetTicks()-move_enemies_tick>600){
            delete dying_enemy;
            dying_enemy = nullptr;
            move_enemies_tick = SDL_GetTicks();
            update_scene();
            for(auto entity:enemys){
                entity->move_frame();
            }           
        }
        draw_enemys();
        draw_scene();
    }
}


void Window::draw_scene(){
    SDL_RenderPresent(get_renderer());
    SDL_RenderClear(get_renderer());
}

void Window::init_game(){
    srand(time(nullptr));
    paused = false;
    game_over = false;
    sprite_sheet = new Texture("images/sheet.png",get_renderer());
    player = new Player(*sprite_sheet,(SDL_Rect){width/2-32,height-70,64,32});
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
    if(enemys.size()==0) init_game();
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

void Window::draw_enemys(){
    if(dying_enemy) dying_enemy->draw();
    player->draw();
    if(player_bullet) player_bullet->draw();
    for(auto entity: enemys){
        entity->redraw();
    }
    for(auto bullet: enemy_bulltets){
        bullet->draw();
    }
}