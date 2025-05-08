#pragma once

#include "jengine/basics/Vector.hpp"
#include "jengine/basics/Object.hpp"

class Entity : public Object
{
public:
    Vector velocity;

    Entity();

    Entity(Vector position);

    Entity(Vector position, Vector velocity);

    virtual ~Entity();

    Vector getPosition() const;
    void setPosition(Vector newPosition);

    Vector getGlobalPosition() const;
    void setGlobalPosition(Vector newPosition);

    // Don't override, only for internal usage.
    void __update_global_position();

    bool addChild(Object *object) override;

private:
    Vector position;

    Vector globalPosition;
};