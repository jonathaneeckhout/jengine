#pragma once

#include "jengine/Vector.hpp"
#include "jengine/Object.hpp"

class Entity : public Object
{
public:
    Vector velocity;

    Entity();

    Entity(Vector position);

    virtual ~Entity();

    Vector getPosition();
    void setPosition(Vector newPosition);

    Vector getGlobalPosition();
    void setGlobalPosition(Vector newPosition);

    // Don't override, only for internal usage.
    void __update_global_position();

private:
    Vector position;

    Vector globalPosition;
};