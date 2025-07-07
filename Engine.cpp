#include "Engine.h"
#include <memory>

Engine::Engine(std::string map_path){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    this->map_path = map_path;
    this->is_running = 1;
    this->window = SDL_CreateWindow("Raycaster engine",625,675,SDL_WINDOW_FULLSCREEN);
    this->renderer = SDL_CreateRenderer(window,NULL);
    this->font = TTF_OpenFont("./JetBrainsMonoNerdFont-Regular.ttf", 16);
    this->font_box.x = OFFSET;
    this->font_box.y= (OFFSET + BOX_SIZE)*24;
    this->font_box.w=300;
    this->font_box.h=50;
    this->frame_start_time = std::chrono::steady_clock::now();
    
    // Initialize a player entity at the moment
    entities.push_back(std::make_shared<player>()); 
}

void Engine::init(){
    map.init(this->renderer,map_path);
    for (std::shared_ptr<game_object> en : entities){
        en->init(this->renderer,map);
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

void Engine::update(){

    this->frame_end_time = std::chrono::steady_clock::now();
    this->frame_time = this->frame_end_time - this->frame_start_time;
    this->frame_rate = (1/this->frame_time.count())*1000;
    this->frame_start_time = this->frame_end_time;
    
    float frame_time_sec = frame_time.count()/1000;
     for (std::shared_ptr<game_object> en : entities){
        en->update(frame_time_sec);
    }   

}

void Engine::Draw() {
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_Surface* text_frame_rate = TTF_RenderText_Blended(font,std::format("Frame Rate {}",frame_rate).c_str(),0, SDL_Color{.r = 255,.g = 255,.b = 255});
    if (!text_frame_rate) std::cerr << "Could not create a surface" <<SDL_GetError() <<std::endl;
    SDL_Texture* frame_texture = SDL_CreateTextureFromSurface(renderer,text_frame_rate);
    SDL_RenderTexture(renderer,frame_texture,NULL,&font_box);

    // Draw the map
    map.draw();
    //Render all the entities
    for (std::shared_ptr<game_object> en : entities ){
        en->draw();
    }
    SDL_RenderPresent(renderer);
}

bool Engine::IsRunning(){
    return this->is_running;
}
