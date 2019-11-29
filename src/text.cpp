#include "text.h"

TextCache::TextCache(SDL_Renderer * target){
    renderer = target;
}

void TextCache::SetFont(string font, string location){
    if (characters.find(font) == characters.end()){
        string font_path = location + font;
        TTF_Font * loaded_font = TTF_OpenFont(font_path.c_str(), 12);
        for (int i=0; i < 90; i++){
            char c = ' ' + i;
            string character = string(1, c);
            SDL_Surface * surface = TTF_RenderText_Solid(loaded_font, character.c_str(), {255, 255, 255});
            characters[font][c] = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_SetTextureBlendMode(characters[font][c], SDL_BLENDMODE_ADD);
            SDL_FreeSurface(surface);
        }
        TTF_CloseFont(loaded_font);
    }
    current_font = font;
}

int TextCache::RenderText(string text, int x, int y, int size, SDL_Color color, int offset){
    if (current_font == ""){return -1;}
    int d_x = (x - (size/2));
    int d_y = (y - (size/2));

    d_rect = {d_x, d_y, size, size};
    for (auto c: text){
        if (c == '\n'){
            d_rect.x = d_x;
            d_rect.y += size;
        }
        else {
            SDL_SetTextureColorMod(characters[current_font][c], color.r, color.g, color.b);
            SDL_RenderCopy(renderer, characters[current_font][c], NULL, &d_rect);
            d_rect.x += size + offset;
        }
    }

    return 1;
}

TextCache::~TextCache(){
    for (const auto &saved : characters){
        for (const auto &character : saved.second){
            SDL_DestroyTexture(character.second);
        }
    }
}

