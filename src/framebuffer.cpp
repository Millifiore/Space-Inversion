#include "framebuffer.h"

Framebuffer::Framebuffer(SDL_Window * window, SDL_Renderer * target) {
    renderer = target;
    pixel_format = SDL_GetWindowPixelFormat(window);
}

Framebuffer::~Framebuffer(){
    for (auto const& buffer: buffers){
        SDL_DestroyTexture(buffer.second);
    }
}

void Framebuffer::CreateBuffer(string name, int width, int height){
    buffers[name] = SDL_CreateTexture(renderer, pixel_format, SDL_TEXTUREACCESS_TARGET, width, height);
}

int Framebuffer::SetActiveBuffer(string name){
    if (buffers.find(name) != buffers.end()){
        SDL_SetRenderTarget(renderer, buffers[name]);
        return 1;
    }
    return 0;
}

void Framebuffer::UnsetBuffers(){
    SDL_SetRenderTarget(renderer, NULL);
}

int Framebuffer::RenderBuffer(string name, int x, int y, int w, int h, SDL_RendererFlip flip){
    d_rect = {(x - (w/2)), (y - (h/2)), w, h};
    if (buffers.find(name) != buffers.end()){
        SDL_RenderCopyEx(renderer, buffers[name], NULL, &d_rect, NULL, NULL, flip);
        return 1;
    }
    return 0;
}