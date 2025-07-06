#include "player.h"
#include <iostream>
player::player(){
    this->renderer = nullptr;
    this->bb.x = 50;
    this->bb.y = 50;
    this->bb.w = 50;
    this->bb.h = 50;
}

void player::init(SDL_Renderer* renderer){
    this->renderer = renderer;
}

void player::handle_events(SDL_Event e){
    if(e.key.key == SDLK_W){
        this->bb.y -= 5;
    } else if(e.key.key == SDLK_S){
        this->bb.y += 5;
    } else if(e.key.key == SDLK_A){
        this->bb.x -= 5;
    } else if(e.key.key == SDLK_D){
        this->bb.x += 5;
    }
}

void player::draw(){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderFillRect(renderer,&bb);
}
