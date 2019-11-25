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
    bullet.x = (x_pos - int(bullet.w / 2)) ;
    bullet.y = (y_pos - int(bullet.h / 2));  

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &bullet);
}

bool Bullet::IsTouchingRect(SDL_Rect* rect){
    if (SDL_HasIntersection(&bullet, rect)){
        return true;
    }
    return false;
}

Bullet::~Bullet(){}