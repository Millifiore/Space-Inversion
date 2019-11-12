#include "keyboard.h"

KeyboardManager::KeyboardManager(){
    memset(previous_keystate, 0 , sizeof(Uint8)*SDL_NUM_SCANCODES);
    current_keystate = SDL_GetKeyboardState(NULL);
}

void KeyboardManager::Process(){
    /* 
        The state of the previous keys are kept to make sure that we can properly process
        if a key WAS pressed, or if it is currently BEING pressed.
    */
    memcpy(previous_keystate, current_keystate, sizeof(Uint8)*SDL_NUM_SCANCODES);
    
}

bool KeyboardManager::KeyIsPressed(int scancode) {
    // This fucntion returns wether the key is currently being pressed or not (i.e. held down).
    return current_keystate[scancode];
}

bool KeyboardManager::KeyWasPressed(int scancode) {
    // This function returns wether the key was pressed (i.e. pressed then let go)
    if ((!previous_keystate[scancode]) && (current_keystate[scancode])){
        return true;
    }
    return false;
}