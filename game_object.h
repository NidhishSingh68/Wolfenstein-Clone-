#include "SDL3/SDL.h"

class game_object{
public:    
    game_object() = default;
    virtual void init(SDL_Renderer* renderer) = 0;
    virtual void handle_events(SDL_Event ev) = 0;
    virtual void draw() = 0;
    virtual ~game_object();
};
