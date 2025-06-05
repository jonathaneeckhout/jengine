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

std::vector<CollisionComponent *> Physics::checkCollision(const CollisionComponent &collision)
{
    std::vector<CollisionComponent *> collisions;

    for (const auto &collider : colliders)
    {
        if (collider == &collision)
        {
            continue;
        }

        if (collision.collidesWith(*collider))
        {
            collisions.push_back(collider);
        }
    }

    return collisions;
}