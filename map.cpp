#include "map.h"

void map::init(SDL_Renderer* renderer, std::string path){
    BOX_SIZE = 25;
    OFFSET = 1;
    map_load.init(path);
    this->renderer = renderer;
    this->map_array = map_load.generate_map_list(); 
    grid_box.x = 0;
    grid_box.y = 0;
    grid_box.w = BOX_SIZE;
    grid_box.h = BOX_SIZE;

}

void map::draw(){
    // Render the Grid
    grid_box.y = OFFSET;
    grid_box.x = OFFSET;
    for(int i = 0 ; i < map_array.size() ; i++ ) {
        for(int j = 0 ; j< map_array[0].size() ;j++ ) {
            if (map_array[i][j] == 1) SDL_SetRenderDrawColor(renderer,255,255,255,255);
            else SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderFillRect(renderer,&grid_box);
            grid_box.x += (BOX_SIZE + OFFSET);
        }

        grid_box.x = OFFSET;
        grid_box.y +=(BOX_SIZE+OFFSET);
    }
    
}
std::vector<std::vector<int>>& map::get_map(){
    return this->map_array;
}
