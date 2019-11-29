#include "enemy.h"
#include "math.h"
#include "player.h"

Enemy::Enemy(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player){
    renderer = cache->renderer;
    type = t;
    this->player = player;
    this->cache = cache;

    x_pos = x;
    y_pos = y;
    starting_xpos = x_pos;
    starting_ypos = y_pos;
    width = w;
    height = h;

    d_rect.x = x;
    d_rect.y = y;
    d_rect.w = w;
    d_rect.h = h;

    sprites["DEFAULT"] = nullptr;
    sprites["DYING"] = nullptr;
    state = "";
    default_speed = 8;
    speed = default_speed;
    projectile_speed = 4;
    cooldown_time = .3;

}

void Enemy::Process(Clock * clock, int height){
    // Animate the current sprite if it has an animation 
    sprites[state]->Animate(clock);

    // If dying animation finished, the sprite is dead.
    if (state == "DYING"){
        if (sprites[state]->finished){
            dead = true;
        }
        moving = false;
    }

    if (dead){
        x_pos = 0;
        y_pos = 0;
    }

    else {
        if (moving){
            if (direction == "left"){
                x_pos -= ((speed * 10) * clock->delta_time_s);
            }
            if (direction == "right"){
                x_pos += ((speed * 10) * clock->delta_time_s);
            }
            if (direction == "up"){
                y_pos -= ((speed * 10) * clock->delta_time_s);
            }
            if (direction == "down"){
                y_pos += ((speed * 10) * clock->delta_time_s);
            }
        }
    }

    // move bullets in the list/vector down screen.
    int i = 0;
    for (auto bullet: bullets){
        
        bullet->Process(clock);
        if (bullet->y_pos >= height){
            if (find(erased.begin(), erased.end(), i) == erased.end()){
                erased.push_back(i);
            }
        }
        i++;
    }

    // erase bullets if they are off screen.
    for (auto index: erased){
        delete bullets[index];
        bullets.erase(bullets.begin()+index);
    }

    // if there is a cooldown, count down the cooldown until it reaches the limit, then disable the cooldown.
    // this is done so that an enemy can only add a bullet in certain intervals.
    if (attack_cooldown){
        cooldown_timer += clock->delta_time_s;
        if (cooldown_timer >= cooldown_time){
            cooldown_timer = 0;
            attack_cooldown = false;
        }
    }

    erased.clear();
}

bool Enemy::canShoot(){
    return y_pos < player->y_pos;
}

void Enemy::Move(string d){
    if (d == "none")
        moving = false;
    else{
        moving = true;
        direction = d;
    } 
}

void Enemy::SetPos(int x, int y){
    x_pos = x;
    y_pos = y;
}

void Enemy::Reset(){
    for (auto sprite : sprites){
        sprite.second->Reset();
    }
    dead = false;
    state = "DEFAULT";
    SetPos(starting_xpos, starting_ypos);
    for (int i = 0; i < bullets.size(); i++){
        if (find(erased.begin(), erased.end(), i) == erased.end()){
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }  
    }
}

bool Enemy::Attack(){
    /*
    (TODO) Use this logic specifically for the villain 2 subclass when it is utilized.
           villain 1 should only shoot bullets in a downward location towards the player.
    */
    float angle_to_player = 270;

    if (state == "DEFAULT"){
        if ((!bullets.size()) && !attack_cooldown){
            bullets.push_back(
                new Projectile(cache, x_pos,
                                    (y_pos + (d_rect.w/2)) - 20, 10, 10, angle_to_player, {255, 0, 0, 255}, projectile_speed)
            );
            attack_cooldown = true;
            return true;
        }
    }
    return false; 
}

bool Enemy::TouchingBullet(SDL_Rect * rect){
    for (auto bullet: bullets){
        if (SDL_HasIntersection(&bullet->hitbox, rect)){
            return true;
        }
    }
    return false;
}

void Enemy::Render(){
    
    d_rect.x = (x_pos - int(d_rect.w / 2));
    d_rect.y = (y_pos - int(d_rect.h / 2));
    d_rect.w = sprites[state]->d_rect.w;
    d_rect.h = sprites[state]->d_rect.h;

    // Set the position of the rendered sprite to be the same position as the enemy
    sprites[state]->SetPos(x_pos, y_pos);

    // Render any bullets if they exist.
    for (auto bullet: bullets){
        bullet->Render();
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &d_rect);

    if (!dead){
        // Render the enemy ship if the enemy isn't dead.
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        sprites[state]->Render();
    }  
}

Enemy::~Enemy(){
    for (auto const sprite: sprites){
        delete sprite.second;
    }

    for (int i = 0; i < bullets.size(); i++){
        delete bullets[i];
        bullets.erase(bullets.begin() + i);
    }
}

Villian1::Villian1(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player)
: Enemy(cache, x, y, w, h, src, t, player) {
    SDL_Rect s_rect;
    s_rect = {30, 24, 40, 40};
    
    sprites["DEFAULT"] = new Sprite(cache, s_rect, d_rect, "resources/villain1.bmp");
    sprites["DYING"] = new AnimatedSprite(cache, {0, 0, 64, 64}, {d_rect.x, d_rect.y, d_rect.w + 60, d_rect.h + 60}, "resources/explosion.bmp", 64, 4, .1);
    state = "DEFAULT";
    default_speed = 8;
    speed = default_speed;
    projectile_speed = 3;
    cooldown_time = .3;

}

bool Villian1::Attack(){

    float angle_to_player = 270;

    if (state == "DEFAULT"){
        if ((!bullets.size()) && !attack_cooldown && canShoot()){
            bullets.push_back(
                new Blaster(cache, x_pos,
                                    (y_pos + (d_rect.w/2)) - 20, 20, 20, angle_to_player, {255, 0, 0, 255}, projectile_speed)
            );
            attack_cooldown = true;
            return true;
        }
    }
    return false; 
}

Villian2::Villian2(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player): Enemy(cache,x,y,w,h,src,t,player){
    SDL_Rect s_rect;
    s_rect = {15, 15, 20, 20};
    
    sprites["DEFAULT"] = new Sprite(cache, s_rect, d_rect, "resources/villain2.bmp");
    sprites["DYING"] = new AnimatedSprite(cache, {0, 0, 64, 64}, {d_rect.x, d_rect.y, d_rect.w + 60, d_rect.h + 60}, "resources/explosion.bmp", 64, 4, .1);
    state = "DEFAULT";
    default_speed = 8;
    speed = default_speed;
    projectile_speed = 4;
    cooldown_time = .3;

}

bool Villian2::Attack(){

    float angle_to_player = (-atan2((player->y_pos-y_pos),(player->x_pos-x_pos))) * (180 /PI);

    if (state == "DEFAULT"){
        if ((!bullets.size()) && !attack_cooldown){
            bullets.push_back(
                new Projectile(cache, x_pos,
                                    (y_pos + (d_rect.w/2)) - 20, 10, 10, angle_to_player, {255, 0, 0, 255}, projectile_speed)
            );
            attack_cooldown = true;
            return true;
        }
    }
    return false; 
}