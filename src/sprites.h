#pragma once
#include <map>
#include "headers.h"

class SpriteCache{
private:
    map<string, SDL_Texture *> textures = {}; 

public:
    SDL_Renderer * renderer;

    SpriteCache(SDL_Renderer *);
    SDL_Texture * LoadTexture(string);
    ~SpriteCache();
};


class Sprite {
public:
    SDL_Texture * texture;
    SDL_Rect d_rect;
    SDL_Rect s_rect;
    SDL_Renderer * renderer;
    SDL_RendererFlip flip;

    bool finished = false;
    Sprite(SpriteCache * cache, SDL_Rect s, SDL_Rect d, string filepath, SDL_RendererFlip f = SDL_FLIP_NONE);
    void SetDestinationR(SDL_Rect * r);
    virtual void Animate(Clock * clock);
    void Render();
    ~Sprite();
};


class AnimatedSprite : public Sprite {
private:
    int frame_offset;
    int number_of_frames;
    int current_frame = 1;
    double update_time;
    double time_passed;

public:
   
    AnimatedSprite(SpriteCache * cache, SDL_Rect s, SDL_Rect d, string filepath, int f_o, int n_o_f, double ut, SDL_RendererFlip f = SDL_FLIP_NONE);
    void Animate(Clock * clock);
    ~AnimatedSprite();
};