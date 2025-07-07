#include "SDL3/SDL.h"
#include "map.h"

class game_object{
public:    
    virtual void init(SDL_Renderer* renderer,map& map) = 0;
    virtual void handle_events(SDL_Event ev) = 0;
    virtual void update(float delta_time) = 0;
    virtual void draw() = 0;
    virtual ~game_object();
};
