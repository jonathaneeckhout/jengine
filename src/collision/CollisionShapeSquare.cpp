#include "jengine/collision/CollisionShapeSquare.hpp"

CollisionShapeSquare::CollisionShapeSquare(Vector position, Vector size) : CollisionShape(position), size(size) {}

bool CollisionShapeSquare::collidesWith(const Vector &point) const
{

    const Vector position = getGlobalPosition();

    return point.x > position.x && point.x < position.x + size.x && point.y > position.y && point.y < position.y + size.y;
}

bool CollisionShapeSquare::collidesWith(const CollisionShape &other) const
{
    return other.collidesWithSquare(*this);
}

bool CollisionShapeSquare::collidesWithSquare(const CollisionShapeSquare &square) const
{
    if (!(viewLayer & square.inLayer))
    {
        return false;
    }

    const Vector position = getGlobalPosition();
    const Vector otherPosition = square.getGlobalPosition();

    return position.x + size.x > otherPosition.x &&
           position.x < otherPosition.x + square.size.x &&
           position.y + size.y > otherPosition.y &&
           position.y < otherPosition.y + square.size.y;
}