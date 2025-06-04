#include "jengine/components/CollisionComponent.hpp"

CollisionComponent::CollisionComponent(TransformComponent *transform) : transform(transform) {}

int CollisionComponent::addCollisionHandler(std::function<void(Object *object, bool collides)> handler)
{
    int id = nextHandlerId++;
    collisionHandlers[id] = std::move(handler);
    return id;
}

void CollisionComponent::removeCollisionHandler(int id)
{
    collisionHandlers.erase(id);
}