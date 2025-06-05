#include "jengine/factories/collisions.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/components/SquareCollisionComponent.hpp"

namespace jengine
{
    namespace collisions
    {
        Object *createSquareCollision(Vector position, Vector size)
        {
            auto obj = new Object();

            auto transform = new TransformComponent(position);
            obj->addComponent(transform);

            auto collision = new SquareCollisionComponent(transform, size);
            obj->addComponent(collision);

            return obj;
        }

    }
}