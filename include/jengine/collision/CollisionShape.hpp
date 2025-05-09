#pragma once

#include <cstdint>

#include "jengine/entities/Entity.hpp"

class CollisionShape : public Entity
{
public:
    // TODO: add layer the shape is in
    // TODO: add layer the shape is looking at
    // TODO: add function callbacks when other shape enters collision area
    uint32_t layer = 0x0001;

    CollisionShape(Vector position);
    virtual ~CollisionShape();

    virtual bool collidesWith(const Vector &point) const = 0;
    virtual bool collidesWith(const class CollisionShapeSquare &square) const = 0;
};