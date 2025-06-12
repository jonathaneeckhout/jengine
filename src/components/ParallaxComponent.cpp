#include <SDL3_image/SDL_image.h>
#include "jengine/components/ParallaxComponent.hpp"
#include "jengine/core/Game.hpp"

ParallaxComponent::ParallaxComponent(
    Vector position,
    Vector direction,
    float speed,
    const std::string &resourceName)
    : position(position), speed(speed)
{
    transform = new TransformComponent(position, direction);
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

    Vector window_size = Game::getInstance()->renderer->getWindowSize();

    tiles_x = window_size.x / texture_width + 2;
    tiles_y = window_size.y / texture_height + 2;

    texture = SDL_CreateTextureFromSurface(Game::getInstance()->renderer->renderer, surface);
    SDL_DestroySurface(surface);
}

ParallaxComponent::~ParallaxComponent()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void ParallaxComponent::update(float dt)
{
    scroll_offset.x += transform->velocity.x * speed * dt;
    scroll_offset.y += transform->velocity.y * speed * dt;

    if (scroll_offset.x >= texture_width)
    {
        scroll_offset.x -= texture_width;
    }
    if (scroll_offset.x < 0)
    {
        scroll_offset.x += texture_width;
    }

    if (scroll_offset.y >= texture_height)
    {
        scroll_offset.y -= texture_height;
    }
    if (scroll_offset.y < 0)
    {
        scroll_offset.y += texture_height;
    }
}

void ParallaxComponent::output()
{
    SDL_Renderer *renderer = Game::getInstance()->renderer->renderer;

    Vector base_pos = transform->getGlobalPosition();

    for (int x = -1; x < tiles_x; ++x)
    {
        for (int y = -1; y < tiles_y; ++y)
        {
            float drawX = base_pos.x + x * texture_width - scroll_offset.x;
            float drawY = base_pos.y + y * texture_height - scroll_offset.y;

            SDL_FRect rect = {
                centered ? drawX - texture_width / 2.0f : drawX,
                centered ? drawY - texture_height / 2.0f : drawY,
                float(texture_width),
                float(texture_height)};

            SDL_RenderTexture(renderer, texture, NULL, &rect);
        }
    }
}
