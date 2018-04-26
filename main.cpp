#include "sdl.hpp"
#include "statemanager.h"
#include "window.h"

#include "Log.h"

int main(int argc, char *args[]){

    SDL::init();

    int width = 800;
    int height = 600;

    Window window(width, height, "Test Window");
    
    StateManager manager(&window);

    manager.run();

    return 0;
}