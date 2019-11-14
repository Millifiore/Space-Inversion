#pragma once
#include "headers.h"
#include "player.h"
#include "framebuffer.h"
#include "enemy.h"
#include "text.h"

class Hud{
    public:
        Player * player;
        int score = 0;
        int highscore;
        vector<Sprite *> lives;
        Framebuffer * framebuffer;
        int enemy_size = -1;
        Sprite * life_sprite;
        TextCache * text_cache;


        Hud(SpriteCache *,Framebuffer *, Player *, TextCache *);
        
        void Process(Clock * clock, vector<Enemy *>);
        ~Hud();
        
        void Process();
        void Render();
};