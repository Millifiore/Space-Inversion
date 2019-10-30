#pragma once
#include "headers.h"
#include "functions.h"
#include "player.h"

class SpaceInversion{
private:

    // Private SDL variables
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Event event;

    // Private general variables
    int WIDTH = 1280, HEIGHT = 720;
    Uint32 WINDOW_FLAGS = SDL_WINDOW_SHOWN;
    Uint32 RENDERER_FLAGS = 0;

    //Private objects
    const Uint8 * keyboard;
    Clock clock;
    SpriteCache * cache;
    Player * p1;

    // Private functions
    void Process();
    void Render();

public:
    // Variables
    int running;

    // Functions
    SpaceInversion();

    int Start(int argc, char ** argv);
    void Loop();
    void End();

    ~SpaceInversion();
};