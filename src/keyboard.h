#pragma once
#include "headers.h"

class KeyboardManager {
    private: 
        // variables
        const Uint8 * instance_keystate;
        Uint8 previous_keystate[SDL_NUM_SCANCODES];
        Uint8 current_keystate[SDL_NUM_SCANCODES];
    public:
        // functions
        KeyboardManager();
        void Process();
        bool KeyIsPressed(int scancode);
        bool KeyWasPressed(int scancode);

};