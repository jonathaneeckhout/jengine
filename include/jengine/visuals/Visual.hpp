#pragma once

#include <jengine/Vector.hpp>
#include <jengine/entities/Entity.hpp>
#include <SDL2/SDL.h>

class Visual : public Entity
{
public:
    SDL_Color color = {255, 255, 255, 255};

    Visual();
    Visual(Vector position);

    virtual ~Visual();
};