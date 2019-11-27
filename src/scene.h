#pragma once
#include "headers.h"
#include "jukebox.h"
#include "enemy.h"
#include "player.h"
#include "text.h"
#include "framebuffer.h"
#include "controller.h"
#include "hud.h"
#include "bullets.h"

class LevelScene {
private:
    vector<Bullet *> stars_l1;
    vector<Bullet *> stars_l2;
    vector<Enemy * > enemies = {};
    vector<int> erased_enemy_i = {};
    Player * player = nullptr;
    double countdown;
    double shoot_timer;
    double shot_interval;
    string direction = "left";
    string enemy_state = "PHASE_LEFT";
    string last_state;
    int enemies_dead = 0;
    SDL_Renderer * renderer;
    Framebuffer * framebuffer;
    Hud * hud;
    SDL_RendererFlip * flip;
public:
    bool starting;
    bool running;
    bool finished;
    LevelScene(SDL_Renderer * renderer,Framebuffer * Framebuffer,SpriteCache * ,TextCache *,SDL_RendererFlip * flip);
    
    void AddEnemy(Enemy * enemy);
    void AddPlayer(Player * player);
    void CreateHUD(Player * player);
    void Process(Clock * clock, KeyboardManager * keyboard, ControllerManager * controllers, Jukebox * jukebox, int width, int height);
    void ManageEnemies(Clock * clock, ControllerManager * controllers, Jukebox * jukebox, int width, int height);
    void RenderScene();

    ~LevelScene();
};

class MenuScene {
    
};