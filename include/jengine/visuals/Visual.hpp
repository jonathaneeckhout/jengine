#pragma once

#include <SDL3/SDL.h>

#include "jengine/basics/Vector.hpp"
#include "jengine/entities/Entity.hpp"

class Visual : public Entity
{
public:
    Visual();
    Visual(Vector position);

    ~Visual();

    virtual void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

protected:
    SDL_Color color = {255, 255, 255, 255};
};