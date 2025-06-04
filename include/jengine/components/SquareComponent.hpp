#pragma once

#include <SDL3/SDL.h>

#include "jengine/components/Component.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/basics/Vector.hpp"

class SquareComponent : public Component
{
public:
    SquareComponent(TransformComponent *transform, Vector size = {32.0, 32.0}, SDL_Color color = {255, 255, 255, 255});

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { color = {r, g, b, a}; };

    void output() override;

private:
    TransformComponent *transform = nullptr;

    Vector size;

    SDL_Color color = {255, 255, 255, 255};
};
