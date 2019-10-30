#include "player.h"

Player::Player(SpriteCache * cache, int x, int y, int w, int h, string src, SDL_RendererFlip flip){
    renderer = cache->renderer;
    x_pos = x;
    y_pos = y;
    width = w;
    height = h;
    texture = cache->LoadTexture(src); 
    orientation = flip;
    s_rect.x = 14;
    s_rect.y = 14;
    s_rect.w = 20;
    s_rect.h = 20;
}

void Player::Process(Clock clock){
    // if the player is moving, move either left or right.
    if (moving){
        if (direction == "left"){
            x_pos -= ((speed * 100) * clock.delta_time_s);
        }
        if (direction == "right"){
            x_pos += ((speed * 100) * clock.delta_time_s);
        }
    }

    // move bullets in the list/vector up screen.
    int i = 0;
    for (auto bullet: bullets){
        
        bullet->y_pos -= ((bullet_speed * 100) * clock.delta_time_s);
        if (bullet->y_pos <= 0){
            erased.push_back(i);
        }
        i++;
    }

    // erase bullets if they are off screen.
    for (auto index: erased){
        delete bullets[index];
        bullets.erase(bullets.begin()+index);
    }

    // if there is a cooldown, count down the cooldown until it reaches the limit, then disable the cooldown.
    // this is done so that a player can only add a bullet in certain intervals.
    if (attack_cooldown){
        cooldown_timer += clock.delta_time_s;
        if (cooldown_timer >= .3){
            cooldown_timer = 0;
            attack_cooldown = false;
        }
    }

    erased.clear();
}

void Player::Move(string d){
    if (d == "none")
        moving = false;
    else{
        moving = true;
        direction = d;
    }
    
}

void Player::Attack(){
    // we check the size of the bullet array to make sure that only 3 bullets are on screen at once.
    if ((bullets.size() < 3) && !attack_cooldown){
        bullets.push_back(
            new Bullet(renderer, x_pos + (int(width/2) - 10),
                                y_pos - 10, 10, 10, SDL_Color({255, 255, 0, 255}))
        );
        attack_cooldown = true;
    }
}

void Player::Render(){
    d_rect.x = x_pos;
    d_rect.y = y_pos;
    d_rect.w = width;
    d_rect.h = height;

    // Render any bullets if they exist.
    for (auto bullet: bullets){
        bullet->Render();
    }

    // Render the player ship.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderCopyEx(renderer, texture, &s_rect, &d_rect, NULL, NULL, orientation);
}

Player::~Player(){
    for (int i = 0; i < bullets.size(); i++){
        delete bullets[i];
        bullets.erase(bullets.begin() + i);
    }

}