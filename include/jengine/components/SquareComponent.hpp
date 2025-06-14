#pragma once

#include <SDL3/SDL.h>

#include "jengine/basics/Object.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/basics/Vector.hpp"

class SquareComponent : public Object
{
public:
    SquareComponent(Vector position, Vector size = {32.0, 32.0}, SDL_Color color = {255, 255, 255, 255});

    void setSize(Vector newSize) { size = newSize; };

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { color = {r, g, b, a}; };

    void output() override;

    void setCentered(bool center);

private:
    Vector position;
    bool centered = false;

    TransformComponent *transform = nullptr;

    Vector size;

    SDL_Color color = {255, 255, 255, 255};
};
