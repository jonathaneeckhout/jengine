#pragma once

#include "jengine/components/Component.hpp"
#include "jengine/basics/Vector.hpp"

class TransformComponent : public Component
{
public:
    Vector velocity;

    TransformComponent(Vector position = {0, 0}, Vector velocity = {0, 0});

    const Vector &getPosition() const { return position; };
    void setPosition(Vector newPosition);

    const Vector &getGlobalPosition() const { return globalPosition; };

private:
    Vector position;
    Vector globalPosition;
};
