#pragma once
#include "headers.h"
#define PI 3.1415926

class Projectile{
    private:
        SDL_Renderer * renderer;
        int width, height;
        SDL_Color color;
        Clock * clock;
    public:
        double x_pos, y_pos;
        SDL_Rect hitbox;
        bool hit = false;
        float angle;
        int speed;

        Projectile(SDL_Renderer *,int x, int y, int w, int h, float angle, SDL_Color, int speed);
        ~Projectile();
        void Process(Clock *);
        void Render();
        bool IsTouchingRect(SDL_Rect *);
        
};