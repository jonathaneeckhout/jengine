#include <SDL3_image/SDL_image.h>

#include "jengine/components/SpriteComponent.hpp"
#include "jengine/core/Game.hpp"

SpriteComponent::SpriteComponent(Vector position, const std::string &resourceName) : position(position)
{
    transform = new TransformComponent(position);
    addChild(transform);

    auto imgIO = Game::getInstance()->resources->getResource(resourceName);
    if (imgIO == nullptr)
    {
        return;
    }

    SDL_Surface *surface = IMG_LoadPNG_IO(imgIO);
    if (surface == NULL)
    {
        return;
    }

    texture_width = surface->w;
    texture_height = surface->h;

    texture = SDL_CreateTextureFromSurface(Game::getInstance()->renderer->renderer, surface);
    if (texture == NULL)
    {
        SDL_DestroySurface(surface);
        return;
    }

    SDL_DestroySurface(surface);
}

SpriteComponent::~SpriteComponent()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void SpriteComponent::output()
{
    Vector position = transform->getGlobalPosition();

    SDL_FRect rect;

    if (centered)
    {
        rect = {position.x - (texture_width / 2), position.y - (texture_height / 2), float(texture_width), float(texture_height)};
    }
    else
    {
        rect = {position.x, position.y, float(texture_width), float(texture_height)};
    }

    SDL_RenderTexture(Game::getInstance()->renderer->renderer, texture, NULL, &rect);
}