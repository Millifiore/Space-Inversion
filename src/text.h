#pragma once
#include "headers.h"

class TextCache {
    private:
        map<string, map<char, SDL_Texture *>> characters;
        SDL_Renderer * renderer;
        string current_font = "";
    public:
        SDL_Rect d_rect;
        TextCache(SDL_Renderer *);
        ~TextCache();
        void SetFont(string font, string location = "resources/font/");
        int RenderText(string text, int x, int y, int size, SDL_Color color = {0, 0, 0, 255}, int offset = 5);
};