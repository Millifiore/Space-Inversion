#include "game.h"

SpaceInversion::SpaceInversion(){};

int SpaceInversion::Start(int argc, char** argv){
    // Process command line arguments if needed.
        // ...
    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_GAMECONTROLLER);
    Mix_Init(MIX_INIT_MOD);
    TTF_Init();

    atexit(SDL_Quit);
    atexit(Mix_Quit);
    atexit(TTF_Quit);
   

    // Create window
    window = SDL_CreateWindow("Space Inversion - by Sardonicals", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                WIDTH, HEIGHT, WINDOW_FLAGS);
    if (!window){
        ShowError("Space Inversion Error!","Couldn't create window: ", "Window creation failed!: ", true);
        return 0;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, RENDERER_FLAGS);
    if (!renderer){
        ShowError("Space Inversion Error!", "Couldn't create renderer: ", "Renderer failed!: ", true);
        return 0;
    }

    // Initialize random seed
    srand(time(NULL));

    // Load window icon
    SDL_Surface * icon = SDL_LoadBMP("resources/icon.bmp");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    // Create event handler
    event = SDL_Event();

    // Start clock
    clock = Clock();

    // Initialize objects
    jukebox = new Jukebox();
    mouse = new MouseManager();
    keyboard = new KeyboardManager();
    controllers = new ControllerManager();
    framebuffer = new Framebuffer(window, renderer);
    text = new TextCache(renderer);
    cache = new SpriteCache(renderer);
    p1 = new Player(cache, 640, 600, 50, 50, "resources/player.bmp");

    text->SetFont("joystix.ttf");

    menu = new MenuScene(cache, framebuffer);
    game_scene = CreateScene(cache, framebuffer,text ,p1, "resources/levels/level2.mx", &flip);
    framebuffer->CreateBuffer("MENU", WIDTH, HEIGHT);
    framebuffer->CreateBuffer("GAME", GAME_WIDTH, GAME_HEIGHT);
    framebuffer->CreateBuffer("HUD", GAME_WIDTH, HEIGHT);
    
    // Start running the app
    running = true;

    return 1;
}


void SpaceInversion::Loop(){
    #ifndef __EMSCRIPTEN__
    while (running) {
    #endif

        Process();
        Render();

        SDL_Delay(5);

    #ifndef __EMSCRIPTEN__
    }
    #endif
}

void SpaceInversion::Process(){
    // Clock tick
    clock.Tick();

    // Render scale
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

    // Keyboard and Mouse
    keyboard->Process();
    mouse->Process();

    if (keyboard->KeyIsPressed(SDL_SCANCODE_ESCAPE)){
        running = false;
    } 

    //Event Loop
    while (SDL_PollEvent(&event)){ 
        if (event.type == SDL_WINDOWEVENT_RESIZED){
            WIDTH = event.window.data1;
            HEIGHT = event.window.data2;
        }

        controllers->ProcessControllerEvents(&event);

        if (event.type == SDL_QUIT){
            running = false;
            break;
        }
    }

    // General Game loop stuff goes here 
    controllers->ProcessControllerButtonState();

    if (keyboard->KeyWasPressed(SDL_SCANCODE_F)){
        if (flip == SDL_FLIP_NONE){
            flip = SDL_FLIP_VERTICAL;
        }
        else{
            flip = SDL_FLIP_NONE;
        }
    }
    if (state == "MENU"){
        menu->Process(&clock, mouse, jukebox, &state, game_scene);
    }
    if (state == "GAME") {
        game_scene->Process(&clock, keyboard, controllers, jukebox, GAME_WIDTH, GAME_HEIGHT);

    }
    
}

void SpaceInversion::Render(){
    if (state == "MENU"){
        menu->RenderScene();
    }
    if (state == "GAME"){
        game_scene->RenderScene();
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (state == "MENU"){
        framebuffer->RenderBuffer("MENU", WIDTH/2, HEIGHT/2, WIDTH, HEIGHT);
    }
    if (state == "GAME"){
        framebuffer->RenderBuffer("HUD",WIDTH/2, HEIGHT/2, GAME_WIDTH, HEIGHT);
        framebuffer->RenderBuffer("GAME", WIDTH/2, HEIGHT/2, GAME_WIDTH, GAME_HEIGHT, flip);
    }

    SDL_RenderPresent(renderer);
}

SpaceInversion::~SpaceInversion(){
    delete game_scene;
    delete menu;
    delete p1;
    delete cache;
    delete text;
    delete framebuffer;
    delete controllers;
    delete jukebox;
    delete mouse;
    delete keyboard;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}