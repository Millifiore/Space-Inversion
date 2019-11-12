#pragma once
#include "headers.h"


class Framebuffer {
    private:
        map<string, SDL_Texture *> buffers;
        SDL_Rect d_rect = {};
        uint32_t pixel_format;

    public:
        SDL_Renderer * renderer;

        Framebuffer(SDL_Window * window, SDL_Renderer * target);
        ~Framebuffer();

        void CreateBuffer(string name, int width, int height);
        int SetActiveBuffer(string name);
        void UnsetBuffers();
        int RenderBuffer(string name, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE);

};