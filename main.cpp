#include "Engine.h"

int main(){
    Engine raycaster("./map.txt");
    raycaster.init();
    while(raycaster.IsRunning()){
        raycaster.HandleEvents();
        raycaster.update();
        raycaster.Draw();
    }
}
