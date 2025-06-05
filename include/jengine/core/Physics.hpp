#pragma once
#include <vector>

#include "jengine/components/CollisionComponent.hpp"

class Physics
{
public:
    Physics();
    ~Physics();

    void physics(float dt);

    void registerCollider(CollisionComponent *collider);
    void unregisterCollider(CollisionComponent *comp);

    const std::vector<CollisionComponent *> &getColliders() { return colliders; };

private:
    std::vector<CollisionComponent *> colliders;
};