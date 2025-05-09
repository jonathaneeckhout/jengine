#pragma once

#include "jengine/collision/CollisionShape.hpp"

class CollisionShapeSquare : public CollisionShape
{
public:
    Vector size = {0, 0};

    CollisionShapeSquare(Vector position, Vector size);

    bool collidesWith(const Vector &point) const override;
    bool collidesWith(const CollisionShape &other) const override;
    bool collidesWithSquare(const CollisionShapeSquare &square) const override;
};