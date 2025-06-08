#pragma once

#include <cstdint>
#include <unordered_set>
#include <unordered_map>
#include <functional>

#include "jengine/basics/Object.hpp"
#include "jengine/basics/Vector.hpp"
#include "jengine/components/TransformComponent.hpp"

class CollisionComponent : public Object
{
public:
    uint32_t inLayer = 0x00000001;
    uint32_t viewLayer = 0x00000001;
    bool center = false;

    TransformComponent *transform = nullptr;

    CollisionComponent(TransformComponent *transform);

    void __addToGame() override;
    void __removeFromGame() override;

    virtual bool collidesWith(const CollisionComponent &other) const = 0;
    virtual bool collidesWithSquare(const class SquareCollisionComponent &square) const = 0;

    void checkCollisions(const std::vector<CollisionComponent *> &allColliders);

private:
    std::unordered_set<CollisionComponent *> currentCollisions;
    std::unordered_set<CollisionComponent *> previousCollisions;
};