#include "game_object.h"
#include <cmath>
#include <iostream>
#include <SDL3/SDL_rect.h>

#define PI 3.14159265
#define BOX_SIZE 25

enum player_state{
    STATIONARY,
    MOVING
};

class player : public game_object{

private:
    SDL_Renderer* renderer;
    SDL_FRect bb; //Bounding box
    SDL_FPoint dir;
    float angle;
    float velocity;
    player_state state;
    map* curr_map; // Okay please change this

public:
    player();
    void init(SDL_Renderer* renderer,map& curr_map) override;
    void draw() override;
    void update(float delta_time) override;
    void handle_events(SDL_Event ev) override;
};



