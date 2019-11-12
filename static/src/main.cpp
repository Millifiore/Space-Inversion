#include "headers.h"
#include "game.h"


//Event Filter for potentially mobile devices and consoles
int Filter(void * userdata, SDL_Event * event){
        SpaceInversion * game = static_cast<SpaceInversion*>(userdata);
    switch (event->type) {
        case SDL_APP_WILLENTERBACKGROUND:
            game->running = false;
            return 0;

        case SDL_APP_WILLENTERFOREGROUND:
            game->running = true;
            return 0;

        default:
            return 1;
    }
}

#ifdef __EMSCRIPTEN__
void RunAppLoop(void * userdata){
    SpaceInversion * game = static_cast<SpaceInversion*>(userdata);
    game->Loop();
}
#endif

int main(int argc, char ** argv){
    SpaceInversion game;

    if (!game.Start(argc, argv)){
        return -1;
    }

    SDL_SetEventFilter(Filter, (void*)&game);
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(RunAppLoop, (void*)&game, 0, 1);
    #else 
    game.Loop();
    #endif
   
    return 0;
}

