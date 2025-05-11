#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "jengine/basics/Object.hpp"
#include "jengine/collision/CollisionShape.hpp"

class Physics : public Object
{
public:
    ~Physics();

    // Delete copy constructor
    Physics(const Physics &) = delete;

    static Physics *getInstance();
    static void deleteInstance();

    bool addCollisionShape(CollisionShape &shape);
    bool removeCollisionShape(const CollisionShape &shape);

    std::vector<CollisionShape *> checkCollision(const CollisionShape &shape);

private:
    static Physics *instancePtr;

    std::unordered_map<std::string, CollisionShape *> collisionShapes;

    Physics();
};