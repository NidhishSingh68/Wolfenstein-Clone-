#include "game_object.h"

class player : public game_object{

private:
    SDL_Renderer* renderer;
    SDL_FRect bb; //Bounding box
public:
    player();
    void init(SDL_Renderer* renderer) override;
    void draw() override;
    void handle_events(SDL_Event ev) override;
};



