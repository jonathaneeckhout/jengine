#include <iostream>

#include "jengine/core/Renderer.hpp"

Renderer *Renderer::instancePtr = NULL;

const Vector Renderer::windowSize = {800, 600};

Renderer::Renderer() : Object()
{
    name = "Renderer";

    window = SDL_CreateWindow("JEngine Game",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              int(windowSize.x), int(windowSize.y),
                              SDL_WINDOW_SHOWN);

    if (!window)
    {
        throw std::runtime_error("Failed to create window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
        instancePtr = NULL;
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
