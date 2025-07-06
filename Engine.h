#include "map_loader.h"
#include "player.h"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_pixels.h>
#include <chrono>
#include <format>
#include <ratio>

#define FRAME_RATE 60.f
#define FRAME_TIME ((1/FRAME_RATE)*1000) // For ms

#define BOX_SIZE 25
#define OFFSET 1


class Engine{
   
private:
    std::vector<std::vector<int>> map_grid; 
    std::vector<SDL_Event> frame_events;
    std::vector<std::shared_ptr<player>> entities;
    map_loader map;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_FRect font_box;
    SDL_FRect grid_box;
    SDL_Event e;
    std::chrono::time_point<std::chrono::steady_clock> frame_start_time;
    std::chrono::time_point<std::chrono::steady_clock> frame_end_time;
    std::chrono::duration<float,std::milli> frame_time;
    float frame_rate;
    bool is_running;

public:

    // Creates window,renderer,and read the map
    Engine(std::string map_path);
    void init();
    bool IsRunning();
    void HandleEvents();
    void Draw();
};
