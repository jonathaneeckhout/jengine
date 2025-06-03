#pragma once

#include "jengine/components/Component.hpp"
#include "jengine/collision/CollisionShape.hpp"

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(CollisionShape *collisionShape = nullptr);
    ~PhysicsComponent();

    void moveAndStop(float dt);

private:
    CollisionShape *collisionShape = nullptr;
};
