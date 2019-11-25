#pragma once
#include "headers.h"
#include "sprites.h"
#include "projectile.h"

class Player{
private:
    map<string, Sprite *> sprites;
    SDL_RendererFlip orientation;
    int width, height;
    bool moving;
    string direction;
    SDL_Renderer * renderer;
    bool shield;

public:
    vector<int> erased;
    string state;
    SDL_Rect d_rect = {};
    double x_pos, y_pos;
    int lives = 3;
    int bullet_speed = 4;
    int speed = 18;
    bool attack_cooldown;
    double cooldown_timer;
    bool attacking = false;
    vector<Projectile *> bullets = {};
    Player(SpriteCache * cache, int x, int y, int w, int h, string src, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void Process(Clock * clock);
    void Move(string d);
    bool Attack();
    bool TouchingBullet(SDL_Rect * rect);
    bool TouchingEnemy(SDL_Rect * rect);

    void Render();
    ~Player();
};