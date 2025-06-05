#include <cassert>

#include "jengine/components/PhysicsComponent.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/core/Game.hpp"

PhysicsComponent::PhysicsComponent(
    TransformComponent *transform,
    CollisionComponent *collision)
    : transform(transform),
      collision(collision)
{
    setName("PhysicsComponent");

    assert(transform != nullptr && "Missing transform component");
    assert(collision != nullptr && "Missing collision component");
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::moveAndStop(float dt)
{
    Vector newPosition = transform->getPosition() + transform->velocity * dt;

    // Cache the old position
    Vector oldPosition = transform->getPosition();

    // Try setting the new position
    transform->setPosition(newPosition);

    // Set back the old position if the object collides with others
    if (Game::getInstance()->physics->checkCollision(*collision).size() > 0)
    {
        transform->setPosition(oldPosition);
    }
}
