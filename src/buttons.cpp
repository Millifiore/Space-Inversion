#include "buttons.h"

Button::Button(int x, int y, int w, int h, SpriteCache * cache){
    x_pos = x;
    y_pos = y;
    area.x = x;
    area.y = y;
    area.w = w;
    area.h = h;
    renderer = cache->renderer;
}

Button::~Button(){}

bool Button::MouseTouching(MouseManager * mouse){
    return mouse->IsTouching(&area);
}

bool Button::MouseClicking(MouseManager * mouse){
    return MouseTouching(mouse) && mouse->IsClicking(&area);
}

void Button::Process(Clock * clock){}

void Button::Render(){}


SpriteButton::SpriteButton(SpriteCache * cache, string filepath, int x, int y, int w, int h, SDL_Rect src, int frames, int offset, double update_time)
: Button(x, y, w, h, cache){
    sprites["DEFAULT"] = new Sprite(cache, src, area, filepath);
    sprites["TOUCHED"] = new AnimatedSprite(cache, src, area, filepath, offset, frames, update_time);
    state = "DEFAULT";
    is_touched = false;
}

void SpriteButton::Process(Clock * clock){
    if (is_touched) {
        state = "TOUCHED";
    }
    else {
        state = "DEFAULT";
    }
    sprites[state]->SetPos(x_pos, y_pos);
    area = sprites[state]->d_rect;
    sprites[state]->Animate(clock);
}

bool SpriteButton::MouseTouching(MouseManager * mouse){
    is_touched = mouse->IsTouching(&area);
    return is_touched;
}

void SpriteButton::Render(){
    sprites[state]->Render();
}