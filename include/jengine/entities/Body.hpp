#pragma once

#include "jengine/basics/Vector.hpp"
#include "jengine/entities/Entity.hpp"
#include "jengine/collision/CollisionShape.hpp"

class Body : public Entity
{
public:
    float speed = 0.0;
    CollisionShape *collisionShape = nullptr;

    Body();

    Body(Vector position);

    Body(Vector position, Vector velocity);

    virtual ~Body();

    void moveAndSlide(float dt);
    void moveAndStop(float dt);
};