#include "player.h"
player::player(){
    this->renderer = nullptr;
    this->bb.x = 50;
    this->bb.y = 50;
    this->bb.w = 10;
    this->bb.h = 10;
}

void player::init(SDL_Renderer* renderer,map& map){
    this->renderer = renderer;
    this->angle = 0;
    //Creates a unit vector
    this->dir.x = 1;
    this->dir.y = 0;
    this->state = STATIONARY;
    this->velocity = 100;
    this->curr_map = &map;
}

void player::handle_events(SDL_Event e){
    if( (e.key.key == SDLK_W || e.key.key == SDLK_S) && (e.key.type == SDL_EVENT_KEY_DOWN) ){
        this->state = MOVING;
    } else if(e.key.key == SDLK_A || e.key.key == SDLK_D){
        if(e.key.key == SDLK_A ) this->angle -= 0.2;
        else this->angle += 0.2;
        this->dir.x = cos(angle);
        this->dir.y = sin(angle);
    } 
    if (e.key.type == SDL_EVENT_KEY_UP){
        this->state = STATIONARY;
    }
}

void player::update(float delta_time){
    // Player movement
    if(this->state == MOVING) {
        this->bb.x += cos(angle)*this->velocity * delta_time;
        this->bb.y += sin(angle)*this->velocity * delta_time;
    }   
}

void player::draw(){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderFillRect(renderer,&bb);
    // Rendering the direction line
    float start_posx,start_posy,end_posx,end_posy;
    start_posx = bb.x + bb.w/2;
    start_posy = bb.y + bb.h/2;
    end_posx = start_posx + 20*dir.x;
    end_posy = start_posy + 20*dir.y;
    // SDL_RenderLine(renderer,start_posx,start_posy,end_posx,end_posy);
    // Render raycast lines
    
    float delta_dist_x,delta_dist_y,side_dist_x,side_dist_y;
    int map_x,map_y,index_x,index_y;
    bool hit;
    map_x = (int) bb.x;
    map_y = (int) bb.y;
    index_x = map_x / 25;
    index_y = map_y / 25;
    side_dist_x = map_x + BOX_SIZE - bb.x;
    side_dist_y = map_y + BOX_SIZE - bb.y;
    delta_dist_x = (angle == 0 ) ? 1e30 : BOX_SIZE / tan(angle);
    delta_dist_y = (angle == 0) ? 1e30 : BOX_SIZE * tan(angle);
    std::vector<std::vector<int>>& map_array = curr_map->get_map();
    while(!hit){
        // Check if no wall at side_dist_x or side_dist_y
        if (map_array[index_x][index_y] == 1){
            hit = 1;
        } else {
            if (side_dist_x < side_dist_y ) {
                index_x += 1;
                side_dist_x += delta_dist_x;
            } else {
                side_dist_y += delta_dist_y;
                index_y += 1;
            }            
        }
    } 

    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    // Once complete draw the line
    SDL_RenderLine(renderer,start_posx,start_posy,side_dist_x,side_dist_y);
}
