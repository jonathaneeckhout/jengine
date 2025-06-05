#pragma once

#include "jengine/basics/Object.hpp"
#include "jengine/components/TransformComponent.hpp"

    class PhysicsComponent : public Object
{
public:
    PhysicsComponent(TransformComponent *transform);
    ~PhysicsComponent();

    void moveAndStop(float dt);

private:
    TransformComponent *transform = nullptr;
};
