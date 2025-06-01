#pragma once

#include "jengine/basics/Vector.hpp"
#include "jengine/entities/Entity.hpp"
#include "jengine/collision/CollisionShape.hpp"

class Body : public Entity
{
public:
   CollisionShape * collisionShape;

    Body();

    Body(Vector position);

    Body(Vector position, Vector velocity);

    virtual ~Body();

    void moveAndSlide(float dt);
    void moveAndStop(float dt);
};