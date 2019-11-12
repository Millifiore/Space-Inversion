#pragma once
#include "headers.h"

class Bullet {
private:
SDL_Renderer * renderer;
    int width, height;
    SDL_Color color;
public:
    float x_pos, y_pos;
    SDL_Rect bullet;
    Bullet(SDL_Renderer * r, int x, int y, int w, int h, SDL_Color c);
    void Render();
    bool IsTouchingRect(SDL_Rect *);
    ~Bullet();
};