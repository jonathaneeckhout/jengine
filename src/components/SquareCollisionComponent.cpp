#include "jengine/components/SquareCollisionComponent.hpp"

SquareCollisionComponent::SquareCollisionComponent(TransformComponent *transform, Vector size) : CollisionComponent(transform), size(size) {}

bool SquareCollisionComponent::collidesWith(const CollisionComponent &other) const
{
    if (!(viewLayer & other.inLayer))
    {
        return false;
    }

    return other.collidesWithSquare(*this);
}

bool SquareCollisionComponent::collidesWithSquare(const SquareCollisionComponent &square) const
{
    const Vector position = transform->getGlobalPosition();
    const Vector otherPosition = square.transform->getGlobalPosition();

    return position.x + size.x > otherPosition.x &&
           position.x < otherPosition.x + square.size.x &&
           position.y + size.y > otherPosition.y &&
           position.y < otherPosition.y + square.size.y;
}
