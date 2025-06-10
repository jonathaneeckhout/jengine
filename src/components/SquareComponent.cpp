#include <cassert>

#include "jengine/components/SquareComponent.hpp"
#include "jengine/core/Game.hpp"

SquareComponent::SquareComponent(Vector position, Vector size, SDL_Color color) : position(position), size(size), color(color)
{
    setName("SquareComponent");

    transform = new TransformComponent(position);
    addChild(transform);
}

void SquareComponent::output()
{
    Renderer *renderer = Game::getInstance()->renderer;
    if (renderer == nullptr)
    {
        return;
    }

    Vector globalPosition = transform->getGlobalPosition();

    SDL_FRect square = {globalPosition.x, globalPosition.y, size.x, size.y};

    SDL_SetRenderDrawColor(renderer->renderer, color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(renderer->renderer, &square);
}

void SquareComponent::setCentered(bool center)
{
    centered = center;
    if (centered)
    {
        transform->setPosition(position - size / 2);
    }
    else
    {
        transform->setPosition(position);
    }
}