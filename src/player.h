#pragma once
#include "headers.h"
#include "bullets.h"
#include "sprites.h"

class Player{
private:
    SDL_RendererFlip orientation;
    int width, height;
    bool moving;
    vector<int> erased;
    string direction;
    SDL_Renderer * renderer;
    SDL_Texture * texture;
    SDL_Rect d_rect = {};
    SDL_Rect s_rect = {};
    bool shield;

public:
    double x_pos, y_pos;
    int lives = 3;
    int bullet_speed = 12;
    int speed = 7;
    bool attack_cooldown;
    double cooldown_timer;
    vector<Bullet *> bullets;
    Player(SpriteCache * cache, int x, int y, int w, int h, string src, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void Process(Clock clock);
    void Move(string d);
    void Attack();

    void Render();
    ~Player();
};