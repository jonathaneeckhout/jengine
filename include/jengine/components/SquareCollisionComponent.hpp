#pragma once

#include "jengine/components/CollisionComponent.hpp"

class SquareCollisionComponent : public CollisionComponent
{
public:
    SquareCollisionComponent(TransformComponent *transform, Vector size);

    bool collidesWith(const CollisionComponent &other) const;

    bool collidesWithSquare(const SquareCollisionComponent &square) const;

    Vector getSize() { return size; };

private:
    Vector size;
};