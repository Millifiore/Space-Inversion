#include "keyboard.h"

KeyboardManager::KeyboardManager(){
    SDL_memset(previous_keystate, 0 , sizeof(Uint8)*SDL_NUM_SCANCODES);
    SDL_memset(current_keystate, 0 , sizeof(Uint8)*SDL_NUM_SCANCODES);
    instance_keystate = SDL_GetKeyboardState(NULL);
}

void KeyboardManager::Process(){
    /* 
        The state of the previous keys are kept to make sure that we can properly process
        if a key WAS pressed, or if it is currently BEING pressed.
    */
    for (int key = 0; key < SDL_NUM_SCANCODES; key++){
        previous_keystate[key] = current_keystate[key];
    }
    for(int key = 0; key < SDL_NUM_SCANCODES; key++){
        current_keystate[key] = instance_keystate[key];
    }
    
}

bool KeyboardManager::KeyIsPressed(int scancode) {
    // This fucntion returns wether the key is currently being pressed or not (i.e. held down).
    return current_keystate[scancode];
}

bool KeyboardManager::KeyWasPressed(int scancode) {
    // This function returns wether the key was pressed (i.e. pressed then let go)
    return !previous_keystate[scancode] && current_keystate[scancode];
}