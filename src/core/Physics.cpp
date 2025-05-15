#include "jengine/core/Physics.hpp"

Physics *Physics::instancePtr = nullptr;

Physics::Physics() : Object()
{
    setName("Physics");
}

Physics::~Physics() {}

Physics *Physics::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new Physics();
    }
    return instancePtr;
}

void Physics::deleteInstance()
{
    if (instancePtr != nullptr)
    {
        delete instancePtr;
        instancePtr = nullptr;
    }
}

bool Physics::addCollisionShape(std::shared_ptr<CollisionShape> &shape)
{
    if (!shape)
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

std::vector<std::weak_ptr<CollisionShape>> Physics::checkCollision(const CollisionShape &shape)
{
    std::vector<std::weak_ptr<CollisionShape>> collisions;

    for (auto it = collisionShapes.begin(); it != collisionShapes.end();)
    {
        std::shared_ptr<CollisionShape> other = it->second.lock();

        if (!other)
        {
            it = collisionShapes.erase(it);
            continue;
        }

        if (other.get() == &shape)
        {
            ++it;
            continue;
        }

        if (shape.collidesWith(*other))
        {
            collisions.push_back(it->second);
        }

        ++it;
    }

    return collisions;
}