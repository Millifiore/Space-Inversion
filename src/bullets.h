#pragma once
#include "headers.h"

class Bullet {
    private:
    SDL_Renderer * renderer;
        int width, height;
        SDL_Rect bullet;
        SDL_Color color;
    public:
        float x_pos, y_pos;

        Bullet(SDL_Renderer * r, int x, int y, int w, int h, SDL_Color c);
        void Render();
        bool IsTouchingRect();
        ~Bullet();
};