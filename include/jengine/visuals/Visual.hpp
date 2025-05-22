#pragma once

#include <SDL3/SDL.h>

#include "jengine/basics/Vector.hpp"
#include "jengine/entities/Entity.hpp"

class Visual : public Entity
{
public:
    SDL_Color color = {255, 255, 255, 255};

    Visual();
    Visual(Vector position);

    virtual ~Visual();
};