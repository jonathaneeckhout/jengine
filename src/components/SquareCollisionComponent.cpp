#include "jengine/components/SquareCollisionComponent.hpp"

SquareCollisionComponent::SquareCollisionComponent(Vector position, Vector size) : CollisionComponent(position), size(size)
{
    setName("SquareCollisionComponent");
}

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
    Vector aPos = transform->getGlobalPosition();
    Vector aSize = size;
    Vector bPos = square.transform->getGlobalPosition();
    Vector bSize = square.size;

    bool xOverlap = aPos.x < bPos.x + bSize.x && aPos.x + aSize.x > bPos.x;
    bool yOverlap = aPos.y < bPos.y + bSize.y && aPos.y + aSize.y > bPos.y;

    return xOverlap && yOverlap;
}

void SquareCollisionComponent::setCentered(bool center)
{
    centered = center;
    if (centered)
    {
        transform->setPosition(position - size / 2);
    }
    else
    {
        transform->setPosition(position);
    }
}
