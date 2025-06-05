#pragma once

#include "jengine/basics/Object.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/components/CollisionComponent.hpp"

    class PhysicsComponent : public Object
{
public:
    PhysicsComponent(TransformComponent *transform, CollisionComponent *collision);
    ~PhysicsComponent();

    void moveAndStop(float dt);

private:
    TransformComponent *transform = nullptr;
    CollisionComponent *collision = nullptr;
};
