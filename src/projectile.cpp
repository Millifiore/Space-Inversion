#include "projectile.h"
#include "math.h"

Projectile::Projectile(SDL_Renderer * r,int x, int y, int w, int h, float a, SDL_Color c, int bullet_speed){
    renderer = r;
    x_pos = x;
    y_pos = y;
    width = w;
    height = h;
    angle = a;
    this->bullet_speed = bullet_speed;

    hitbox.x = x_pos;
    hitbox.y = y_pos;
    hitbox.h = height;
    hitbox.w = width;
}

void Projectile::Process(Clock * clock){
    x_pos += (cos(angle)*((bullet_speed * 10)) * clock->delta_time_s);
    y_pos += (-sin(angle)*((bullet_speed * 10)) * clock->delta_time_s);
}


void Projectile::Render(){
    hitbox.x = (x_pos - int(hitbox.w/2));
    hitbox.y = (y_pos - int(hitbox.h/2));

    SDL_SetRenderDrawColor(renderer,color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer,&hitbox);
}

bool Projectile::IsTouchingRect(SDL_Rect* rect){
    if (SDL_HasIntersection(&hitbox, rect)){
        return true;
    }
    return false;
}

Projectile::~Projectile(){}