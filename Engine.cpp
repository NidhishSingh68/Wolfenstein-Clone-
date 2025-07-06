#include "Engine.h"
#include <memory>

Engine::Engine(std::string map_path):map(map_path){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    this->is_running = 1;
    this->map_grid = map.generate_map_list(); //Reads the text file into 2D map grid array
    this->window = SDL_CreateWindow("Raycaster engine",625,675,SDL_WINDOW_FULLSCREEN);
    this->renderer = SDL_CreateRenderer(window,NULL);
    this->font = TTF_OpenFont("./JetBrainsMonoNerdFont-Regular.ttf", 16);
    this->font_box.x = OFFSET;
    this->font_box.y= (OFFSET + BOX_SIZE)*map.get_map_dimensions()[0];
    this->font_box.w=300;
    this->font_box.h=50;
    this->grid_box.x = 0;
    this->grid_box.y=0;
    this->grid_box.w = BOX_SIZE;
    this->grid_box.h=BOX_SIZE;
    this->frame_start_time = std::chrono::steady_clock::now();
    
    // Initialize a player entity at the moment
    entities.push_back(std::make_shared<player>()); 
}

void Engine::init(){
    for (std::shared_ptr<game_object> en : entities){
        en->init(this->renderer);
    }
}

void Engine::HandleEvents() {
    while(SDL_PollEvent(&e)){
        if (e.type == SDL_EVENT_QUIT ){
            this->is_running = 0;
        } else {
            this->frame_events.push_back(e); 
        }
    }
    
    for( std::shared_ptr<game_object> en : entities){
        for(SDL_Event e : frame_events){
            en->handle_events(e); //Broadcast all events to all entities
        }
    }
    //Clear all the frame events
    this->frame_events.clear();
}

void Engine::Draw() {
    this->frame_end_time = std::chrono::steady_clock::now();
    this->frame_time = this->frame_end_time - this->frame_start_time;
    this->frame_rate = (1/this->frame_time.count())*1000;
    this->frame_start_time = this->frame_end_time;

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_Surface* text_frame_rate = TTF_RenderText_Blended(font,std::format("Frame Rate {}",frame_rate).c_str(),0, SDL_Color{.r = 255,.g = 255,.b = 255});
    if (!text_frame_rate) std::cerr << "Could not create a surface" <<SDL_GetError() <<std::endl;
    SDL_Texture* frame_texture = SDL_CreateTextureFromSurface(renderer,text_frame_rate);
    SDL_RenderTexture(renderer,frame_texture,NULL,&font_box);

    // Render the Grid
    grid_box.y = OFFSET;
    grid_box.x = OFFSET;
    for(int i = 0 ; i < map_grid.size() ; i++ ) {
        for(int j = 0 ; j< map_grid[0].size() ;j++ ) {
            if (map_grid[i][j] == 1) SDL_SetRenderDrawColor(renderer,255,255,255,255);
            else SDL_SetRenderDrawColor(renderer,0,0,0,255);

            SDL_RenderFillRect(renderer,&grid_box);
            grid_box.x += (BOX_SIZE + OFFSET);
        }

        grid_box.x = OFFSET;
        grid_box.y +=(BOX_SIZE+OFFSET);
    }
    
    //Render all the entities
    for (std::shared_ptr<game_object> en : entities ){
        en->draw();
    }
    SDL_RenderPresent(renderer);
}

bool Engine::IsRunning(){
    return this->is_running;
}
