#include "hud.h"
#include "string.h"

Hud::Hud( SpriteCache * cache,Framebuffer * framebuffer, Player * player, TextCache * t_cache){
    text_cache = t_cache;
    this->player = player;
    this->framebuffer = framebuffer;
    this->renderer = framebuffer->renderer;

    this->life_sprite = new Sprite(cache,{},{19,690,30,50},"resources/life.bmp");
}

void Hud::AddScore(int score){
    this->score+=score;
}

void Hud::UpdateLivesAndScore(){
    this->lives_string = "x " + to_string(player->lives);
    this->score_string = "Score: " + to_string(score);
}

void Hud::Render(){
    framebuffer->SetActiveBuffer("HUD");
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    this->UpdateLivesAndScore();

    text_cache->RenderText(score_string, 19, 20, 40, {0, 128, 128, 255});
    text_cache->RenderText(lives_string, 60, 700, 40, {255, 255, 255, 255});
    life_sprite->Render();

    framebuffer->UnsetBuffers();
}