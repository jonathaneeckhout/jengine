#include "jengine/components/CollisionComponent.hpp"
#include "jengine/core/Game.hpp"

CollisionComponent::CollisionComponent(TransformComponent *transform) : transform(transform) {}

void CollisionComponent::addToGame()
{
    Game::getInstance()->physics->registerCollider(this);
}

void CollisionComponent::removeFromGame()
{
    Game::getInstance()->physics->unregisterCollider(this);
}

void CollisionComponent::checkCollisions(const std::vector<CollisionComponent *> &allColliders)
{
    previousCollisions = std::move(currentCollisions);
    currentCollisions.clear();

    for (CollisionComponent *other : allColliders)
    {
        if (other == this)
            continue;

        if (collidesWith(*other))
        {
            currentCollisions.insert(other);

            if (!previousCollisions.contains(other))
            {
                invokeCollisionHandlers(other, true);
            }
        }
    }

    for (CollisionComponent *prev : previousCollisions)
    {
        if (!currentCollisions.contains(prev))
        {
            invokeCollisionHandlers(prev, false);
        }
    }
}

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

void CollisionComponent::invokeCollisionHandlers(CollisionComponent *collider, bool collides)
{

    for (const auto &[id, handler] : collisionHandlers)
    {
        handler(collider->owner, collides);
    }
}