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