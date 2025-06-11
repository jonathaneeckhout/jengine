#pragma once

#include <SDL3/SDL.h>
#include "jengine/basics/Object.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/basics/Vector.hpp"

class SpriteComponent : public Object
{
public:
    SpriteComponent(Vector position, const std::string &resourceName);

private:
    Vector position;
    TransformComponent *transform = nullptr;

    SDL_Texture *texture = nullptr;
};