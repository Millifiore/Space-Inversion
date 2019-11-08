#include "game.h"

SpaceInversion::SpaceInversion(){};

int SpaceInversion::Start(int argc, char** argv){
    // Process command line arguments if needed.
        // ...
    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_GAMECONTROLLER);

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

    // Create event handler
    event = SDL_Event();

    // Start clock
    clock = Clock();

    // Initialize objects
    cache = new SpriteCache(renderer);
    p1 = new Player(cache, 640, 600, 50, 50, "resources/player.bmp");

    scene = CreateScene(cache, p1, "resources/levels/level.mx");

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

    // render scale
    SDL_RenderSetLogicalSize(renderer, GAME_WIDTH, GAME_HEIGHT);

    // Keyboard
    keyboard = SDL_GetKeyboardState(NULL);

    if (keyboard[SDL_SCANCODE_ESCAPE]){
        running = false;
    } 

    //Event Loop
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            running = false;
            break;
        }
    }

    // General Game loop stuff goes here 
    scene->Process(&clock, keyboard, WIDTH, HEIGHT);

}

void SpaceInversion::Render(){
    //Rendering
    SDL_SetRenderDrawColor(renderer, 29, 41, 81, 255);
    SDL_RenderClear(renderer);

    // General rendering goes here 
    scene->RenderScene();

    SDL_RenderPresent(renderer);

}

SpaceInversion::~SpaceInversion(){
    delete scene;
    delete p1;
    delete cache;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}