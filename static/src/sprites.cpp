#include "sprites.h"
#include "functions.h"

SpriteCache::SpriteCache(SDL_Renderer * r){
    renderer = r;
}

SDL_Texture * SpriteCache::LoadTexture(string filepath){
    if (textures.find(filepath) == textures.end()) {
        SDL_Surface * surface = SDL_LoadBMP(filepath.c_str());
        if (!surface){
            ShowError("Space Inversion Error!", (filepath + " not found!, can't load!"), "file not loaded", false);
        }
        textures[filepath] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    return textures[filepath];
}

SpriteCache::~SpriteCache(){
    for (auto const &instance : textures){
        SDL_DestroyTexture(instance.second);
    }
}




Sprite::Sprite(SpriteCache * cache, SDL_Rect s, SDL_Rect d, string filepath, SDL_RendererFlip f){
    texture = cache->LoadTexture(filepath);
    s_rect = s;
    d_rect = d;
    starting_s_x = s_rect.x;
    starting_s_y = s_rect.y;
    renderer = cache->renderer;
    flip = f;
    x = d_rect.x;
    y = d_rect.y;
}

void Sprite::Animate(Clock * clock){finished = true;}

void Sprite::SetPos(int xpos, int ypos){
    x = xpos;
    y = ypos;
}

void Sprite::SetDestinationR(SDL_Rect * r){
    d_rect.x = r->x;
    d_rect.y = r->y;
    d_rect.w = r->w;
    d_rect.h = r->h;
}

void Sprite::Render(){
    d_rect.x = (x - (d_rect.w / 2));
    d_rect.y = (y - (d_rect.h / 2));
    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    //SDL_RenderFillRect(renderer, &d_rect);
    SDL_RenderCopyEx(renderer, texture, &s_rect, &d_rect, NULL, nullptr, flip);
}

void Sprite::Reset(){}

Sprite::~Sprite(){}




AnimatedSprite::AnimatedSprite(SpriteCache * cache, SDL_Rect s, SDL_Rect d, string filepath, int f_o, int n_o_f, double ut, SDL_RendererFlip f)
: Sprite(cache, s, d, filepath, f) {
    frame_offset = f_o;
    number_of_frames = n_o_f;
    update_time = ut;
    time_passed = 0.0;
}

void AnimatedSprite::Animate(Clock * clock){
    // time passed counts the amount of time that has passed in seconds
    time_passed += clock->delta_time_s;

    // if the time that has passed is the same or greater than the update time, then the animation should change frames.
    if (time_passed >= update_time){
        current_frame += 1;
        s_rect.x += frame_offset;

        if (current_frame <= 1){finished = false;}

        if (current_frame > number_of_frames) {
            finished = true;
            s_rect.x += (-1 * ((number_of_frames - 1) * frame_offset));
            current_frame = 1;
            time_passed = 0;
        }

        // time passed needs to be reset to zero so that the animation can happen within the frame time.
        time_passed = 0.0;
    }
}

void AnimatedSprite::Reset(){
    time_passed = 0.0;
    s_rect.x = starting_s_x;
    s_rect.y = starting_s_y;
    finished = false;
    current_frame = 1;
}

AnimatedSprite::~AnimatedSprite(){}
