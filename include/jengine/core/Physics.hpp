#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

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

    bool addCollisionShape(std::shared_ptr<CollisionShape>& shape);
    bool removeCollisionShape(const std::string& id);

    std::vector<std::weak_ptr<CollisionShape>> checkCollision(const CollisionShape &shape);

private:
    static Physics *instancePtr;

    std::unordered_map<std::string, std::weak_ptr<CollisionShape>> collisionShapes;

    Physics();
};