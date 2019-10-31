#pragma once
#include "headers.h"
#include "sprites.h"
#include "bullets.h"

class Enemy{
private:
    map<string, Sprite *> sprites;
    int width, height;
    bool moving;
    string direction;
    SDL_Renderer * renderer;

public:
    vector<int> erased;
    string type;
    string state;
    SDL_Rect d_rect = {};
    double x_pos, y_pos;
    int bullet_speed;
    int speed;
    int max_bullets;
    bool attack_cooldown;
    double cooldown_timer;
    vector<Bullet *> bullets;
    bool dead = false;

    Enemy(SpriteCache * cache, int x, int y, int w, int h, string src, string t);

    void Process(Clock * clock);
    void Move(string d);
    void SetPos(int x, int y);
    void Attack();
    bool TouchingBullet(SDL_Rect * rect);

    void Render();
    ~Enemy();
};