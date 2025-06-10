#pragma once

#include "jengine/components/CollisionComponent.hpp"

class SquareCollisionComponent : public CollisionComponent
{
public:
    SquareCollisionComponent(Vector position, Vector size);

    bool collidesWith(const CollisionComponent &other) const;

    bool collidesWithSquare(const SquareCollisionComponent &square) const;

    Vector getSize() { return size; };

    void setCentered(bool center);

private:
    Vector size;
};