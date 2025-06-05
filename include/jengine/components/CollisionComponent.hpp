#pragma once

#include <cstdint>
#include <unordered_set>
#include <unordered_map>
#include <functional>

#include "jengine/basics/Component.hpp"
#include "jengine/basics/Vector.hpp"
#include "jengine/components/TransformComponent.hpp"

class CollisionComponent : public Component
{
public:
    uint32_t inLayer = 0x00000001;
    uint32_t viewLayer = 0x00000001;

    TransformComponent *transform = nullptr;

    CollisionComponent(TransformComponent *transform);

    void addToGame() override;
    void removeFromGame() override;

    virtual bool collidesWith(const CollisionComponent &other) const = 0;
    virtual bool collidesWithSquare(const class SquareCollisionComponent &square) const = 0;

    void checkCollisions(const std::vector<CollisionComponent *> &allColliders);

    int addCollisionHandler(std::function<void(Object *object, bool collides)> handler);
    void removeCollisionHandler(int id);

private:
    int nextHandlerId = 1;
    std::unordered_map<int, std::function<void(Object *, bool)>> collisionHandlers;

    std::unordered_set<CollisionComponent *> currentCollisions;
    std::unordered_set<CollisionComponent *> previousCollisions;

    void invokeCollisionHandlers(CollisionComponent *collision, bool collides);
};