#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "jengine/collision/CollisionShape.hpp"

class Physics
{
public:
    Physics();
    ~Physics();

    bool addCollisionShape(CollisionShape *shape);
    bool removeCollisionShape(const std::string &id);

    std::vector<CollisionShape *> checkCollision(const CollisionShape &shape);

private:
    std::unordered_map<std::string, CollisionShape *> collisionShapes;
};