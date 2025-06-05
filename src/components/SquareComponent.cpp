#include <cassert>

#include "jengine/components/SquareComponent.hpp"
#include "jengine/core/Game.hpp"

SquareComponent::SquareComponent(TransformComponent *transform, Vector size, SDL_Color color) : transform(transform), size(size), color(color)
{
    setName("SquareComponent");

    assert(transform != nullptr && "Missing transform component");
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