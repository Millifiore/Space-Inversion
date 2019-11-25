#include "hud.h"
#include "string.h"

Hud::Hud( SpriteCache * cache,Framebuffer * framebuffer, Player * player, TextCache * text_cache){
    this->text_cache = text_cache;
    this->player = player;
    this->framebuffer = framebuffer;
    this->renderer = framebuffer->renderer;

    this->life_sprite = new Sprite(cache, {}, {19,690,50,50},"resources/life.bmp");
}

void Hud::AddScore(int score){
    this->score+=score;
}

void Hud::SetScore(int score){
    this->score = score;
}

void Hud::UpdateLivesAndScore(){
    this->lives_string = to_string(player->lives);
    this->score_string = "Score: " + to_string(score);
}

void Hud::Render(){
    framebuffer->SetActiveBuffer("HUD");
    SDL_SetRenderDrawColor(renderer, 29, 41, 81, 255);
    SDL_RenderClear(renderer);
    this->UpdateLivesAndScore();

    text_cache->RenderText(score_string, 19, 20, 30, {0, 128, 128, 255});
    text_cache->RenderText(lives_string, 60, 700, 30, {0, 128, 128, 255});
    life_sprite->Render();

    framebuffer->UnsetBuffers();
}