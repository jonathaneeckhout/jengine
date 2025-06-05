#pragma once

#include "jengine/basics/Vector.hpp"
#include "jengine/components/SquareComponent.hpp"

namespace jengine
{
    namespace visuals
    {
        Object *createSquare(Vector position, Vector size, SDL_Color color = {255, 255, 255, 255});

        Object *createLabel(Vector position, const std::string &text, unsigned int size, const std::string &resourceName);
    }
}