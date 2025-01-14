#include "player.h"

Player::Player(SpriteCache * cache, int x, int y, int w, int h, string src, SDL_RendererFlip flip){
    renderer = cache->renderer;
    x_pos = x;
    y_pos = y;
    width = w;
    height = h;

    d_rect.x = x;
    d_rect.y = y;
    d_rect.w = w;
    d_rect.h = h;

    moving = false;
    state = "DEFAULT";
    sprites[state] = new Sprite(cache, {30, 24, 37, 37}, d_rect, src);
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

    // move bullets in the list/vector up screen.
    int i = 0;
    for (auto bullet: bullets){
        
        bullet->y_pos -= ((bullet_speed * 100) * clock->delta_time_s);
        if (bullet->y_pos <= 0){
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
    // this is done so that a player can only add a bullet in certain intervals.
    if (attack_cooldown){
        cooldown_timer += clock->delta_time_s;
        if (cooldown_timer >= .3){
            cooldown_timer = 0;
            attack_cooldown = false;
        }
    }

    // Animate the current sprite if it has an animation 
    sprites[state]->Animate(clock);

    
    erased.clear();
}

void Player::Move(string d){
    if (d == "none"){
        this->moving = false;
    }   
    else{
        moving = true;
        direction = d;
    }
    
}

void Player::Attack(){
    // we check the size of the bullet array to make sure that only 3 bullets are on screen at once.
    if (state == "DEFAULT"){
        if ((bullets.size() < 3) && !attack_cooldown){
            bullets.push_back(
                new Bullet(renderer, x_pos,
                                    (d_rect.y + (d_rect.w/2)) - 10, 10, 10, SDL_Color({0, 255, 0, 255}))
            );
            attack_cooldown = true;
        }
    }   
}

bool Player::TouchingBullet(SDL_Rect * rect){
    for (auto bullet: bullets){
        if (SDL_HasIntersection(&bullet->bullet, rect)){
            return true;
        }
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