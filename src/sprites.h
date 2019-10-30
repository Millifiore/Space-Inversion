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