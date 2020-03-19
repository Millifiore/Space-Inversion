#include "headers.h"
#include "game.h"

//Event Filter for potentially mobile devices and consoles
int Filter(void * userdata, SDL_Event * event){
    SpaceInversion * game = static_cast<SpaceInversion*>(userdata);
    switch (event->type) {
        case SDL_WINDOWEVENT:
            {
                switch(event->window.event){
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                    {
                        game->current_width = event->window.data1;
                        game->current_height = event->window.data2;
                    }
                    return 1;

                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        game->Render();
                    }
                    return 1;

                    case SDL_WINDOWEVENT_CLOSE: 
                    {
                        event->type = SDL_QUIT;
                        SDL_PushEvent(event);
                    }
                    return 0;
                }
            }
            return 1;

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
    emscripten_set_main_loop_arg(RunAppLoop, (void*)&game, 60, 1);
    #else 
    game.Loop();
    #endif
   
    return 0;
}

