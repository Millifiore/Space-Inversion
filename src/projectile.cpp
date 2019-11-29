#include "projectile.h"
#include "math.h"

Projectile::Projectile(SpriteCache * cache,int x, int y, int w, int h, float a, SDL_Color color, int speed){
    this->cache = cache;
    renderer = cache->renderer;
    x_pos = x;
    y_pos = y;
    width = w;
    height = h;
    angle = a * (PI / 180);

    this->speed = speed;
    this->color = color;

    hitbox.x = x_pos;
    hitbox.y = y_pos;
    hitbox.h = height;
    hitbox.w = width;
    
    sprites["DEFAULT"] = new Sprite(cache, {0, 0, 25, 25}, hitbox, "resources/blast.bmp");
}

void Projectile::Process(Clock * clock){
    x_pos += (cos(angle)*(speed * 100)) * clock->delta_time_s;
    y_pos += (-sin(angle)*(speed * 100)) * clock->delta_time_s;
    sprites["DEFAULT"]->Animate(clock);
}


void Projectile::Render(){
    hitbox.x = (x_pos - int(hitbox.w/2));
    hitbox.y = (y_pos - int(hitbox.h/2));
    hitbox.w = sprites["DEFAULT"]->d_rect.w;
    hitbox.h = sprites["DEFAULT"]->d_rect.h;

    // SDL_SetRenderDrawColor(renderer,color.r, color.g, color.b, color.a);
    // SDL_RenderFillRect(renderer,&hitbox);
    sprites["DEFAULT"]->SetPos(x_pos,y_pos);
    sprites["DEFAULT"]->Render();
}

bool Projectile::IsTouchingRect(SDL_Rect * rect){
    return SDL_HasIntersection(&hitbox, rect);
}

Projectile::~Projectile(){
    for (auto const sprite: sprites){
        delete sprite.second;
    }
    sprites.clear();
}

Missile::Missile(SpriteCache * cache,int x, int y, int w, int h, float angle, SDL_Color color, int speed) 
    : Projectile(cache, x, y, w, h, angle, color, speed){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 20, 20}, hitbox, "resources/missle.bmp", 20, 3, .1);
}

Blaster::Blaster(SpriteCache * cache,int x, int y, int w, int h, float angle, SDL_Color color, int speed) 
    : Projectile(cache, x, y, w, h, angle, color, speed){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 6, 6}, hitbox, "resources/blaster.bmp", 6, 2, .06, 0, SDL_FLIP_VERTICAL);
}

Laser::Laser(SpriteCache * cache,int x, int y, int w, int h, float angle, SDL_Color color, int speed) 
    : Projectile(cache, x, y, w, h, angle, color, speed){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 6, 6}, hitbox, "resources/laser.bmp", 6, 2, .06);
}

Laser2::Laser2(SpriteCache * cache, int x, int y, int w, int h, float angle, SDL_Color color, int speed) 
    : Projectile(cache, x, y, w, h, angle, color, speed){
    angle = -(angle - double(270));
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 6, 6}, hitbox,"resources/laser2.bmp", 6, 2, .06, angle, SDL_FLIP_VERTICAL);
}