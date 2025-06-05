#include "jengine/factories/Visuals.hpp"
#include "jengine/basics/Object.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/components/SquareComponent.hpp"

namespace jengine
{
    namespace visuals
    {
        Object *createSquare(Vector position, Vector size, SDL_Color color)
        {
            auto obj = new Object();
            obj->setName("Square");

            auto transform = new TransformComponent(position);
            obj->addChild(transform);

            auto square = new SquareComponent(transform, size, color);
            obj->addChild(square);

            return obj;
        }

    }
}