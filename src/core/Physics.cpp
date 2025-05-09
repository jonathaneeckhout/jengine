#include "jengine/core/Physics.hpp"

Physics *Physics::instancePtr = nullptr;

Physics::Physics() : Object()
{
    name = "Physics";
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

bool Physics::addCollisionShape(CollisionShape &shape)
{
    const std::string &id = shape.getId();
    if (collisionShapes.count(id) > 0)
    {
        return false;
    }

    collisionShapes[id] = &shape;
    return true;
}

bool Physics::removeCollisionShape(const CollisionShape &shape) {
    const std::string &id = shape.getId();

    auto it = collisionShapes.find(id);
    if (it != collisionShapes.end() && it->second == &shape) {
        collisionShapes.erase(it);
        return true;
    }

    return false;
}

std::vector<std::string> Physics::checkCollision(const CollisionShape &shape)
{
    std::vector<std::string> collisions;

    for (const auto &entry : collisionShapes) {
        const std::string &id = entry.first;
        const CollisionShape *other = entry.second;

        if (other == &shape) {
            continue;
        }

        if (shape.collidesWith(*other)) {
            collisions.push_back(id);
        }
    }

    return collisions;
}