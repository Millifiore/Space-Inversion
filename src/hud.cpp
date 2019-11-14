#include "hud.h"

Hud::Hud( SpriteCache * cache,Framebuffer * framebuffer, Player * player, TextCache * text_cache){
    this->text_cache = text_cache;
    this->player = player;
    this->framebuffer = framebuffer;
}

void Hud::Render(){
    framebuffer->SetActiveBuffer("HUD");

    text_cache->RenderText("Hello World!", 19, 20, 40, {0, 128, 128, 255});
    text_cache->RenderText("Hello World!", 19, 700, 40, {255, 255, 255, 255});

    framebuffer->UnsetBuffers();
}