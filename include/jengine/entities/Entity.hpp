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

    const Vector &getPosition() const { return position; };
    void setPosition(Vector newPosition);

    const Vector &getGlobalPosition() const { return globalPosition; };
    void setGlobalPosition(Vector newPosition) { globalPosition = newPosition; };

    // Don't override, only for internal usage.
    void __update_global_position();

    bool addChild(Object *child) override;

private:
    Vector position = {0.0, 0.0};

    Vector globalPosition = {0.0, 0.0};
};