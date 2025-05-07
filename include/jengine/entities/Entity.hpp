#pragma once

#include "jengine/Vector.hpp"
#include "jengine/Object.hpp"

class Entity : public Object
{
public:
    Vector position;

    Vector globalPosition;

    Vector velocity;

    Entity();

    Entity(Vector position);

    virtual ~Entity();

    void __update(float dt) override;
};