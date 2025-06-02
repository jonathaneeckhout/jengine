#include "jengine/core/Physics.hpp"

Physics::Physics() : Object()
{
    setName("Physics");
}

Physics::~Physics() {}

bool Physics::addCollisionShape(CollisionShape *shape)
{
    if (shape == nullptr)
    {
        return false;
    }

    auto id = shape->getId();

    collisionShapes[id] = shape;

    return true;
}

bool Physics::removeCollisionShape(const std::string &id)
{
    auto it = collisionShapes.find(id);

    if (it == collisionShapes.end())
    {
        return false;
    }

    collisionShapes.erase(it);

    return true;
}

std::vector<CollisionShape *> Physics::checkCollision(const CollisionShape &shape)
{
    std::vector<CollisionShape *> collisions;

    for (const auto &collider : collisionShapes)
    {
        if (collider.second == &shape)
        {
            continue;
        }

        if (shape.collidesWith(*collider.second))
        {
            collisions.push_back(collider.second);
        }
    }

    return collisions;
}