#pragma once
#include "headers.h"

class KeyboardManager {
    private:
        Uint8 previous_keystate[SDL_NUM_SCANCODES];
    public:
        // variables
        const Uint8 * current_keystate;

        // functions
        KeyboardManager();
        void Process();
        bool KeyIsPressed(int scancode);
        bool KeyWasPressed(int scancode);

};