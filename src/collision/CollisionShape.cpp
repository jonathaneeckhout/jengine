#include "jengine/collision/CollisionShape.hpp"
#include "jengine/core/Physics.hpp"

CollisionShape::CollisionShape(Vector position) : Entity(position) {}

CollisionShape::~CollisionShape() {}

void CollisionShape::__init()
{
    Physics *physics = Physics::getInstance();

    std::shared_ptr<CollisionShape> self = std::dynamic_pointer_cast<CollisionShape>(shared_from_this());
    if (self)
    {
        physics->addCollisionShape(self);
    }

    Entity::__init();
}

void CollisionShape::__cleanup()
{
    Physics *physics = Physics::getInstance();

    physics->removeCollisionShape(getId());

    for (auto &collider : colliders)
    {
        if (auto col = collider.lock())
        {
            col->removeCollider(this);
        }
    }

    Entity::__cleanup();

    triggerEndHandlers(colliders);
}

void CollisionShape::update(float)
{
    Physics *physics = Physics::getInstance();

    // Remove expired colliders before comparison
    colliders.erase(
        std::remove_if(colliders.begin(), colliders.end(),
                       [](const std::weak_ptr<CollisionShape> &w)
                       { return w.expired(); }),
        colliders.end());

    std::vector<std::weak_ptr<CollisionShape>> newColliders = physics->checkCollision(*this);

    std::vector<std::weak_ptr<CollisionShape>> removedColliders;
    for (const auto &currentWeak : colliders)
    {
        if (currentWeak.expired())
            continue;

        auto current = currentWeak.lock();
        bool stillPresent = false;

        for (const auto &newWeak : newColliders)
        {
            if (auto nw = newWeak.lock())
            {
                if (nw == current)
                {
                    stillPresent = true;
                    break;
                }
            }
        }

        if (!stillPresent)
        {
            removedColliders.push_back(current);
        }
    }

    std::vector<std::weak_ptr<CollisionShape>> addedColliders;
    for (const auto &newWeak : newColliders)
    {
        if (newWeak.expired())
            continue;

        auto newShape = newWeak.lock();
        bool alreadyPresent = false;

        for (const auto &currentWeak : colliders)
        {
            if (auto cw = currentWeak.lock())
            {
                if (cw == newShape)
                {
                    alreadyPresent = true;
                    break;
                }
            }
        }

        if (!alreadyPresent)
        {
            addedColliders.push_back(newShape);
        }
    }

    // Replace current colliders with new ones
    colliders = newColliders;

    triggerEndHandlers(removedColliders);
    triggerStartHandlers(addedColliders);
}

const std::vector<std::weak_ptr<CollisionShape>> CollisionShape::getColliders()
{
    return colliders;
}

void CollisionShape::removeCollider(const CollisionShape *shape)
{
    auto it = std::remove_if(colliders.begin(), colliders.end(),
                             [shape](const std::weak_ptr<CollisionShape> &weakPtr)
                             {
                                 if (auto shared = weakPtr.lock())
                                 {
                                     return shared.get() == shape;
                                 }
                                 return false;
                             });

    if (it != colliders.end())
    {
        colliders.erase(it, colliders.end());
    }
}

void CollisionShape::triggerStartHandlers(std::vector<std::weak_ptr<CollisionShape>> &addedColliders)
{
    for (auto &collider : addedColliders)
    {
        for (auto &handler : collisionStartHandlers)
        {
            handler(collider);
        }
    }
}

void CollisionShape::triggerEndHandlers(std::vector<std::weak_ptr<CollisionShape>> &removedColliders)
{
    for (auto &collider : removedColliders)
    {
        for (auto &handler : collisionEndHandlers)
        {
            handler(collider);
        }
    }
}
