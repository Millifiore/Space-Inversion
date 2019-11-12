#pragma once
#include "headers.h"
#include "functions.h"
#include "scene.h"

class SpaceInversion{
private:

    // Private SDL variables
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Event event;

    // Private general variables
    int WIDTH = 800, HEIGHT = 600;
    int GAME_WIDTH = 800, GAME_HEIGHT = 600;
    Uint32 WINDOW_FLAGS = SDL_WINDOW_SHOWN;
    Uint32 RENDERER_FLAGS = SDL_RENDERER_PRESENTVSYNC;

    // Private objects
    KeyboardManager keyboard;
    Clock clock;
    SpriteCache * cache;
    LevelScene * scene;
    Player * p1;
    MouseManager mouse;

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