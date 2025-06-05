#pragma once

#include "jengine/basics/Component.hpp"
#include "jengine/components/TransformComponent.hpp"

    class PhysicsComponent : public Component
{
public:
    PhysicsComponent(TransformComponent *transform);
    ~PhysicsComponent();

    void moveAndStop(float dt);

private:
    TransformComponent *transform = nullptr;
};
