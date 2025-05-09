#include "jengine/collision/CollisionShape.hpp"
#include "jengine/core/Physics.hpp"

#include <iostream>

CollisionShape::CollisionShape(Vector position) : Entity(position)
{
    Physics *physics = Physics::getInstance();

    physics->addCollisionShape(*this);
}

CollisionShape::~CollisionShape()
{
    Physics *physics = Physics::getInstance();

    physics->removeCollisionShape(*this);
}

void CollisionShape::update(float)
{
    Physics *physics = Physics::getInstance();

    std::vector<std::string> newColliders = physics->checkCollision(*this);

    // Find removed colliders
    std::vector<std::string> removedColliders;
    for (const auto &currentCollider : colliders)
    {
        if (std::find(newColliders.begin(), newColliders.end(), currentCollider) == newColliders.end())
        {
            removedColliders.push_back(currentCollider);
        }
    }

    // Find new colliders
    std::vector<std::string> newlyAddedColliders;
    for (const auto &newCollider : newColliders)
    {
        if (std::find(colliders.begin(), colliders.end(), newCollider) == colliders.end())
        {
            newlyAddedColliders.push_back(newCollider);
        }
    }

    colliders = newColliders;

    for (const auto &collider : removedColliders)
    {
        for (const auto &handler : collisionEndHandlers)
        {
            handler(collider);
        }
    }

    for (const auto &collider : newlyAddedColliders)
    {
        for (const auto &handler : collisionStartHandlers)
        {
            handler(collider);
        }
    }
}