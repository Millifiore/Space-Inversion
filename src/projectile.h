#pragma once
#include "headers.h"
#include "sprites.h"
#define PI 3.1415926

class Projectile{
    protected:
        SDL_Renderer * renderer;
        SpriteCache * cache;
        int width, height;
        SDL_Color color;
        Clock * clock;
    public:
        double x_pos, y_pos;
        SDL_Rect hitbox;
        bool hit = false;
        float angle;
        int speed;
        map<string, Sprite *> sprites;

        Projectile(SpriteCache *,int x, int y, int w, int h, float angle, SDL_Color, int speed);
        virtual ~Projectile();
        virtual void Process(Clock *);
        virtual void Render();
        bool IsTouchingRect(SDL_Rect *);
        
};

class Missile : public Projectile{
    public:
        Missile(SpriteCache *, int x, int y, int w, int h, float angle, SDL_Color, int speed);
};

class Blaster : public Projectile{
    public:
        Blaster(SpriteCache *, int x, int y, int w, int h, float angle, SDL_Color, int speed);
};

class Laser : public Projectile{
    public:
        Laser(SpriteCache *, int x, int y, int w, int h, float angle, SDL_Color, int speed);
};

class Laser2 : public Projectile {
    public:
        Laser2(SpriteCache *, int x, int y, int w, int h, float angle, SDL_Color, int speed);
};