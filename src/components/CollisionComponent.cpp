#include "jengine/components/CollisionComponent.hpp"
#include "jengine/core/Game.hpp"

CollisionComponent::CollisionComponent(TransformComponent *transform) : transform(transform)
{
    setName("CollisionComponent");

    events.createEvent<Object *, bool>("onCollision");
}

void CollisionComponent::__addToGame()
{
    Object::__addToGame();

    Game::getInstance()->physics->registerCollider(this);
}

void CollisionComponent::__removeFromGame()
{
    Object::__removeFromGame();

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
                events.trigger("onCollision", other->getParent(), true);
            }
        }
    }

    for (CollisionComponent *prev : previousCollisions)
    {
        if (!currentCollisions.contains(prev))
        {
            events.trigger("onCollision", prev->getParent(), false);
        }
    }
}
