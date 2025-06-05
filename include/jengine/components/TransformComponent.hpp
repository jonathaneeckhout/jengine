#pragma once

#include "jengine/basics/Object.hpp"
#include "jengine/basics/Vector.hpp"

class TransformComponent : public Object
{
public:
    Vector velocity;

    TransformComponent(Vector position = {0, 0}, Vector velocity = {0, 0});

    const Vector &getPosition() const { return position; };
    void setPosition(Vector newPosition);

    const Vector &getGlobalPosition();

    void sync(bool shouldDirty) override;

private:
    Vector position;
    Vector globalPosition;

    void updateGlobalPosition();
};
