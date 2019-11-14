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
        string score_string;
        string lives_string;
        vector<Sprite *> lives;
        Framebuffer * framebuffer;
        int enemy_size = -1;
        Sprite * life_sprite;
        TextCache * text_cache;
        SDL_Renderer * renderer;


        Hud(SpriteCache *,Framebuffer *, Player *, TextCache *);

        
        void AddScore(int);
        ~Hud();

        void Process();
        void Render();
        void UpdateLivesAndScore();
};