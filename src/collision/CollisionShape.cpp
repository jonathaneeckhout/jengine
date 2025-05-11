#include "jengine/collision/CollisionShape.hpp"
#include "jengine/core/Physics.hpp"

#include <iostream>

CollisionShape::CollisionShape(Vector position) : Entity(position)
{
    Physics *physics = Physics::getInstance();

    physics->addCollisionShape(*this);
}

CollisionShape::~CollisionShape() {}

void CollisionShape::cleanup()
{
    Physics *physics = Physics::getInstance();

    physics->removeCollisionShape(*this);

    for (auto collider : colliders)
    {
        collider->removeCollider(this);
    }

    triggerEndHandlers(colliders);
}

void CollisionShape::update(float)
{
    Physics *physics = Physics::getInstance();

    std::vector<CollisionShape *> newColliders = physics->checkCollision(*this);

    // Find removed colliders
    std::vector<CollisionShape *> removedColliders;
    for (auto &currentCollider : colliders)
    {
        if (std::find(newColliders.begin(), newColliders.end(), currentCollider) == newColliders.end())
        {
            removedColliders.push_back(currentCollider);
        }
    }

    // Find new colliders
    std::vector<CollisionShape *> addedColliders;
    for (auto &newCollider : newColliders)
    {
        if (std::find(colliders.begin(), colliders.end(), newCollider) == colliders.end())
        {
            addedColliders.push_back(newCollider);
        }
    }

    colliders = newColliders;

    triggerEndHandlers(removedColliders);

    triggerStartHandlers(addedColliders);
}

void CollisionShape::removeCollider(CollisionShape *shape)
{
    auto it = std::remove(colliders.begin(), colliders.end(), shape);
    if (it != colliders.end())
    {
        colliders.erase(it, colliders.end());
    }
}

void CollisionShape::triggerStartHandlers(std::vector<CollisionShape *> &addedColliders)
{
    for (auto &collider : addedColliders)
    {
        for (auto &handler : collisionStartHandlers)
        {
            handler(collider);
        }
    }
}

void CollisionShape::triggerEndHandlers(std::vector<CollisionShape *> &removedColliders)
{
    for (auto &collider : removedColliders)
    {
        for (auto &handler : collisionEndHandlers)
        {
            handler(collider);
        }
    }
}
