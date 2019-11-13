#pragma once
#include "headers.h"
#include "enemy.h"
#include "player.h"
#include "text.h"

class LevelScene {
private:
    vector<Bullet *> stars_l1;
    vector<Bullet *> stars_l2;
    vector<Enemy * > enemies = {};
    vector<int> erased_enemy_i = {};
    Player * player = nullptr;
    double countdown;
    double shoot_timer;
    string direction = "left";
    string enemy_state = "PHASE_LEFT";
    string last_state;
    SDL_Renderer * renderer;
public:
    bool starting;
    bool running;
    bool finished;
    LevelScene(SDL_Renderer * renderer);
    
    void AddEnemy(Enemy * enemy);
    void AddPlayer(Player * player);
    void Process(Clock * clock, KeyboardManager * keyboard, int width, int height);
    void ManageEnemies(Clock * clock, int width, int height);
    void RenderScene();

    ~LevelScene();
};