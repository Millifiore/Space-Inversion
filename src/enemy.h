#pragma once
#include "headers.h"
#include "sprites.h"
#include "projectile.h"
#include "player.h"

class Enemy{
protected:
    map<string, Sprite *> sprites;
    int width, height;
    bool moving;
    string direction;
    int starting_xpos, starting_ypos;
    SDL_Renderer * renderer;
    SpriteCache * cache; 

public:
    vector<int> erased;
    string type;
    string state;
    SDL_Rect d_rect = {};
    double x_pos, y_pos;
    int projectile_speed = 0;
    int default_speed = 0;
    int speed = 0;
    int max_projectiles = 1;
    bool attack_cooldown;
    double cooldown_timer = 0.0;
    double cooldown_time = 0.0;
    vector<Projectile *> bullets = {};
    bool dead = false;
    Player * player;

    Enemy(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player);

    virtual void Process(Clock * clock, int height);
    virtual void Move(string d);
    void SetPos(int x, int y);
    void Reset();
    bool canShoot();
    virtual bool Attack();
    bool TouchingBullet(SDL_Rect * rect);

    virtual void Render();
    virtual ~Enemy();
};

class Villian1: public Enemy{
    public:
        bool Attack();
        Villian1(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player);

};


class Villian2: public Enemy{
    public:
        bool Attack();
        Villian2(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player);
};