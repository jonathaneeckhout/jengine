#include <iostream>

#include "jengine/core/Renderer.hpp"

Renderer::Renderer()
{

    window = SDL_CreateWindow("JEngine Game",
                              static_cast<int>(windowSize.x),
                              static_cast<int>(windowSize.y),
                              SDL_WINDOW_HIGH_PIXEL_DENSITY);

    if (!window)
    {
        throw std::runtime_error("Failed to create window");
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        throw std::runtime_error("Failed to create renderer");
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
}

void Renderer::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(renderer);
}

void Renderer::setWindowSize(Vector newSize)
{
    windowSize = newSize;

    SDL_SetWindowSize(window, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));
}

void Renderer::setWindowTitle(std::string title)
{
    SDL_SetWindowTitle(window, title.c_str());
}
