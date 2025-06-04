#pragma once

#include "jengine/components/Component.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/collision/CollisionShape.hpp"

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(TransformComponent *transform, CollisionShape *collisionShape = nullptr);
    ~PhysicsComponent();

    void moveAndStop(float dt);

private:
    TransformComponent *transform = nullptr;
    CollisionShape *collisionShape = nullptr;
};
