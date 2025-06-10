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

    TransformComponent *transform = nullptr;

    CollisionComponent(Vector position);

    void __addToGame() override;
    void __removeFromGame() override;

    virtual bool collidesWith(const CollisionComponent &other) const = 0;
    virtual bool collidesWithSquare(const class SquareCollisionComponent &square) const = 0;

    void checkCollisions(const std::vector<CollisionComponent *> &allColliders);

    virtual void setCentered(bool center) = 0;

protected:
    Vector position;
    bool centered = false;

private:
    std::unordered_set<CollisionComponent *> currentCollisions;
    std::unordered_set<CollisionComponent *> previousCollisions;
};