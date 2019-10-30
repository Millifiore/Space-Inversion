#include "bullets.h"

Bullet::Bullet(SDL_Renderer * r, int x, int y, int w, int h, SDL_Color c){
    renderer = r;
    x_pos = x;
    y_pos = y;
    width = w;
    height = h;
    color = c;

    bullet.x = x_pos; bullet.y = y_pos; bullet.h = height; bullet.w = width;
}

void Bullet::Render(){
    bullet.x = x_pos;
    bullet.y = y_pos;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &bullet);
}

Bullet::~Bullet(){}