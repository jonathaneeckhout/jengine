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
            obj->setName("SquareCollision");

            auto transform = new TransformComponent(position);
            obj->addChild(transform);

            auto collision = new SquareCollisionComponent(transform, size);
            obj->addChild(collision);

            return obj;
        }

    }
}