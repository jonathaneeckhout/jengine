#include "jengine/collisions.hpp"
#include "jengine/components/TransformComponent.hpp"

namespace jengine
{
    namespace collisions
    {
        Object *createSquareCollision(Vector position, Vector size)
        {
            auto obj = new Object();

            auto transform = new TransformComponent(position);
            obj->addComponent(transform);

            return obj;
        }

    }
}