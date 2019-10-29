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

    // Create event handler
    event = SDL_Event();

    // Start clock
    clock = Clock();

    //Start running the app
    running = true;

    return 1;
}


void SpaceInversion::Loop(){
    #ifndef __EMSCRIPTEN__
    while (running) {
    #endif

        Process();
        Render();

    #ifndef __EMSCRIPTEN__
    }
    #endif
}

void SpaceInversion::Process(){
    //Clock tick
    clock.Tick();
    
    //Event Loop
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            running = false;
            break;
        }
    }

    // General Game loop stuff goes here [...]

}

void SpaceInversion::Render(){
    //Rendering
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderClear(renderer);
    // General rendering goes here [...]
    SDL_RenderPresent(renderer);

}

SpaceInversion::~SpaceInversion(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}