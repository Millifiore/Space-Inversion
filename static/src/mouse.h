#pragma once
#include "headers.h"

class MouseManager{
    private:
        SDL_Rect mouse_rect;
        bool clicked;
    public:
        // variables
        int x_pos;
        int y_pos;
        bool clicking;
        bool has_clicked;

        // functions
        MouseManager();
        void Process();
        bool IsClicking(SDL_Rect * rect);
        bool HasClicked(SDL_Rect * rect);

        void ResetState();

        void Render(SDL_Renderer * renderer);
};