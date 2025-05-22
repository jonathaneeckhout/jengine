#include <iostream>

#include "jengine/core/Renderer.hpp"

Renderer *Renderer::instancePtr = nullptr;

const Vector Renderer::windowSize = {800, 600};

Renderer::Renderer() : Object()
{
    setName("Renderer");

    window = SDL_CreateWindow("JEngine Game",
                              int(windowSize.x),
                               int(windowSize.y),
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

Renderer *Renderer::getInstance()
{
    if (!instancePtr)
    {
        instancePtr = new Renderer();
    }

    return instancePtr;
}

void Renderer::deleteInstance()
{
    if (instancePtr)
    {
        delete instancePtr;
        instancePtr = nullptr;
    }
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

void Renderer::setWindowTitle(std::string title)
{
    SDL_SetWindowTitle(window, title.c_str());
}
