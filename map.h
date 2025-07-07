#pragma once

#include "map_loader.h"
#include <SDL3/SDL.h>

class map{
private:
    SDL_Renderer* renderer;
    std::vector<std::vector<int>> map_array; 
    map_loader map_load;
    SDL_FRect grid_box;
    int BOX_SIZE;
    int OFFSET;

public:
    map() = default;
    void init(SDL_Renderer* renderer,std::string path);
    void draw();
    std::vector<std::vector<int>>& get_map();
    
};
