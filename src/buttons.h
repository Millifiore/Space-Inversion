#pragma once
#include "headers.h"
#include "sprites.h"

class Button {
    protected:
        SDL_Rect area;
        SDL_Renderer * renderer;
        string state;
        
    public:
        bool highlight = false;
        double x_pos;
        double y_pos;

        Button(int x, int y, int w, int h, SpriteCache * cache);
        virtual ~Button();

        virtual bool MouseTouching(MouseManager * mouse);
        virtual bool MouseClicking(MouseManager * mouse);
        virtual void Process(Clock * clock);
        virtual void Render();
};

class SpriteButton : public Button{
    private: 
        map<string, Sprite *> sprites;
        bool is_touched;
    public:
        SpriteButton(SpriteCache * cache, string filepath, int x, int y, int w, int h, SDL_Rect src, int frames = 1, int offset = 0, double update_time = 0 );
        void Process(Clock * clock);
        bool MouseTouching(MouseManager * mouse);
        void Render();
};