#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#define SDL_MAIN_HANDLED
#include "Bullet.hpp"
#include <stdint.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Entity.hpp"
#include "Player.hpp"
#include "EnemyBack.hpp"
#include "Square.hpp"

class Window {
    
    protected:

    uint32_t width=800;
    uint32_t height=600;
    std::string window_name = "INVADERS :3";
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit = false;
    Texture* sprite_sheet = nullptr;
    int cur_direction = 1;

    int enemy_movment_per_frame = 20;
    int enemy_x_distance = 40;
    int enemy_y_distance = 40;

    int player_movement = 20;

    int bullet_movement = 1;

    Entity* dying_enemy = nullptr;
    uint32_t tick_cnt = 0;
    std::vector<Entity*> enemys; 
    Player* player = nullptr;   
    Bullet* player_bullet = nullptr;
    std::vector<Bullet*> enemy_bulltets;

    Square* test_square = nullptr;

    bool game_over = false;
    bool paused = false;

    int bullet_width = 4;
    int bullet_height = 16;

    void handle_mouse(SDL_Event&);
    
    void handle_keyboard(SDL_Event&);

    void handle_quit(SDL_Event&);

    void draw_enemys();
    
    public:

    void init();

    void init_game();

    void set_height(uint32_t height){this->height = height;}

    void set_width(uint32_t width){this->width = width;}

    uint32_t get_width() {return width;}

    uint32_t get_height() {return height;}

    int get_event(SDL_Event& event);

    void handle_event(SDL_Event& event);

    void draw_scene();

    void loop();

    SDL_Renderer* get_renderer() {return renderer;}

    void update_scene();

    ~Window();
};

#endif