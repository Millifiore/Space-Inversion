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
    SpriteCache * cache;
    bool shield;
    double starting_xpos = 0, starting_ypos = 0;

public:
    vector<int> erased;
    string state;
    SDL_Rect d_rect = {};
    double x_pos = 0, y_pos = 0;
    int starting_life = 3;
    int lives = starting_life;
    int projectile_speed = 4;
    int speed = 19;
    bool attack_cooldown = false;
    double respawn_timer = 0;
    double cooldown_timer = 0;
    double cooldown_time = 0;
    double respawning_time = 2;
    int max_projectiles = 3;
    bool attacking = false;
    vector<Projectile *> bullets = {};
    Player(SpriteCache * cache, int x, int y, int w, int h, string src, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void Process(Clock * clock);
    void Move(string d);
    bool Attack();
    void Hurt();
    void SetPos(int, int);
    bool TouchingBullet(SDL_Rect * rect);
    bool TouchingEnemy(SDL_Rect * rect);
    void Reset();

    void Render();
    ~Player();
};