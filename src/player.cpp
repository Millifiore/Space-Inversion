#include "player.h"
#include "projectile.h"

Player::Player(SpriteCache * cache, int x, int y, int w, int h, string src, SDL_RendererFlip flip){
    renderer = cache->renderer;
    this->cache = cache;
    x_pos = x;
    y_pos = y;
    width = w;
    height = h;

    d_rect.x = x;
    d_rect.y = y;
    d_rect.w = w;
    d_rect.h = h;

    moving = false;

    sprites["DEFAULT"] = new Sprite(cache, {30, 24, 37, 37}, d_rect, src);
    sprites["DYING"] = new AnimatedSprite(cache, {0, 0, 64, 64}, {d_rect.x, d_rect.y, d_rect.w + 60, d_rect.h + 60}, "resources/explosion.bmp", 64, 4, .1);
    sprites["RESPAWNING"] = new AnimatedSprite(cache, {30, 24, 37, 37}, d_rect, src, -37, 2, .03);
    state = "DEFAULT";
    cooldown_time = .3;
}

void Player::Process(Clock * clock){
    // if the player is moving, move either left or right.
    if (moving){
        if (direction == "left"){
            x_pos -= ((speed * 10) * clock->delta_time_s);
        }
        if (direction == "right"){
            x_pos += ((speed * 10) * clock->delta_time_s);
        }
    }

    if (state == "DYING"){
        if (sprites[state]->finished){
            sprites[state]->Reset();
            state = "RESPAWNING";
        }
    }

    if (state == "RESPAWNING"){
        respawn_timer += clock->delta_time_s;
        if (respawn_timer >= respawning_time){
            respawn_timer = 0.0;
            state = "DEFAULT";  
        }
    }

    // move bullets in the list/vector up screen.
    int i = 0;
    for (auto bullet: bullets){
        
        bullet->Process(clock);
        if (bullet->y_pos <= 0){
            if (find(erased.begin(), erased.end(), i) == erased.end()){
                erased.push_back(i);
            }
        }
        i++;
    }

    // erase bullets if they are off screen or if they hit something.
    for (auto index: erased){
        delete bullets[index];
        bullets.erase(bullets.begin()+index);
    }

    // if there is a cooldown, count down the cooldown until it reaches the limit, then disable the cooldown.
    // this is done so that a player can only add a bullet in certain intervals.
    if (attack_cooldown){
        cooldown_timer += clock->delta_time_s;
        if (cooldown_timer >= cooldown_time){
            cooldown_timer = 0;
            attack_cooldown = false;
        }
    }

    // Animate the current sprite if it has an animation 
    sprites[state]->Animate(clock);
    
    erased.clear();
}

void Player::Move(string d){
    if ((d == "none") || (state == "DYING")){
        this->moving = false;
    }   
    else{
        moving = true;
        direction = d;
    }
    
}

bool Player::Attack(){
    // we check the size of the bullet array to make sure that only 3 bullets are on screen at once.
    if (state == "DEFAULT"){
        if ((bullets.size() < max_projectiles) && !attack_cooldown){
            bullets.push_back(
                new Laser(cache, x_pos,
                                    (d_rect.y + (d_rect.w/2)) - 10, 15, 20, 90, {0, 255, 0, 255}, projectile_speed)
            );
            attack_cooldown = true;
            return true;
        }
    }
    return false;   
}

void Player::Hurt(){
    lives -= 1;
    state = "DYING";
}

bool Player::TouchingBullet(SDL_Rect * rect){
    for (auto bullet: bullets){
        if (SDL_HasIntersection(&bullet->hitbox, rect)){
            return true;
        }
    }
    return false;
}

bool Player::TouchingEnemy(SDL_Rect * rect){
    if(SDL_HasIntersection(&d_rect,rect)){
        return true;
    }

    return false;
}

void Player::Render(){
    d_rect.x = (x_pos - int(d_rect.w / 2));
    d_rect.y = (y_pos - int(d_rect.h / 2));
    d_rect.w = sprites[state]->d_rect.w;
    d_rect.h = sprites[state]->d_rect.h;

    // Set the position of the rendered sprite to be the same position as the player
    sprites[state]->SetPos(x_pos, y_pos);
    
    // Render any bullets if they exist.
    for (auto bullet: bullets){
        bullet->Render();
    }

    // Render the player ship.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
   sprites[state]->Render();
}

Player::~Player(){
    for (auto const sprite: sprites){
        delete sprite.second;
    }

    for (int i = 0; i < bullets.size(); i++){
        delete bullets[i];
        bullets.erase(bullets.begin() + i);
    }

}