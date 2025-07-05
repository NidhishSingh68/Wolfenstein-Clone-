#include "Engine.h"

int main(){
    Engine raycaster("./map.txt");

    while(raycaster.IsRunning()){
        raycaster.HandleEvents();
        raycaster.Draw();
    }
}
