#include <cassert>

#include "jengine/components/PhysicsComponent.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/core/Game.hpp"

PhysicsComponent::PhysicsComponent(CollisionShape *collisionShape) : collisionShape(collisionShape) {}

PhysicsComponent::~PhysicsComponent()
{
    if (collisionShape != nullptr)
    {
        delete collisionShape;
    }
}

void PhysicsComponent::moveAndStop(float dt)
{
    auto transform = owner->getComponent<TransformComponent>();

    assert(transform != nullptr && "Missing transform component");

    Vector newPosition = transform->getPosition() + transform->velocity * dt;

    if (collisionShape == nullptr)
    {
        transform->setPosition(newPosition);

        return;
    }

    // Cache the old position
    Vector oldPosition = transform->getPosition();

    // Try setting the new position
    transform->setPosition(newPosition);

    // Set back the old position if the object collides with others
    if (Game::getInstance()->physics->checkCollision(*collisionShape).size() > 0)
    {
        transform->setPosition(oldPosition);
    }
}
