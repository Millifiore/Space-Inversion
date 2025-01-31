#pragma once
#include "headers.h"
#include "functions.h"
#include "framebuffer.h"
#include "scene.h"


class SpaceInversion {
private:

    // Private SDL variables
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Event event;

    // Private general variables
    int WIDTH = 1280, HEIGHT = 720;
    int GAME_WIDTH = 800, GAME_HEIGHT = 600;
    Uint32 WINDOW_FLAGS = SDL_WINDOW_SHOWN;
    Uint32 RENDERER_FLAGS = SDL_RENDERER_PRESENTVSYNC;
    string state = "MENU";
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    string scene_path = "";

    // Private objects
    KeyboardManager * keyboard;
    ControllerManager * controllers;
    Jukebox * jukebox;
    Clock clock;
    SpriteCache * cache;
    MenuScene * menu;
    LevelScene * game_scene;
    Player * p1;
    MouseManager * mouse;
    Framebuffer * framebuffer;
    TextCache * text;

    // Private functions
    void Process();
    

public:
    // Variables
    int running;
    bool resized = false;
    int current_width = WIDTH, current_height = HEIGHT;
    // Functions
    SpaceInversion();

    int Start(int argc, char ** argv);
    void Loop();
    void End();
    void Render();

    ~SpaceInversion();
};