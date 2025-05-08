#pragma once

#include "jengine/Vector.hpp"
#include "jengine/Object.hpp"

class Entity : public Object
{
public:
    Vector velocity;

    Entity();

    Entity(Vector position);

    Entity(Vector position, Vector velocity);

    virtual ~Entity();

    Vector getPosition();
    void setPosition(Vector newPosition);

    Vector getGlobalPosition();
    void setGlobalPosition(Vector newPosition);

    // Don't override, only for internal usage.
    void __update_global_position();

    bool addChild(Object *object) override;

private:
    Vector position;

    Vector globalPosition;
};