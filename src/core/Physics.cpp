#include "jengine/core/Physics.hpp"

Physics::Physics() {}

Physics::~Physics() {}

void Physics::physics(float)
{
    for (auto *collider : colliders)
    {
        collider->checkCollisions(colliders);
    }
}

void Physics::registerCollider(CollisionComponent *collider)
{
    colliders.push_back(collider);
}

void Physics::unregisterCollider(CollisionComponent *collider)
{
    colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), colliders.end());
}
