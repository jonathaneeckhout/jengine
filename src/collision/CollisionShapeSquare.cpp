#include "jengine/collision/CollisionShapeSquare.hpp"

CollisionShapeSquare::CollisionShapeSquare(Vector position, Vector size) : CollisionShape(position), size(size) {}

bool CollisionShapeSquare::collidesWith(const Vector &point) const
{

    const Vector position = getGlobalPosition();

    return point.x > position.x && point.x < position.x + size.x && point.y > position.y && point.y < position.y + size.y;
}

bool CollisionShapeSquare::collidesWith(const CollisionShape &other) const
{
    if (!(viewLayer & other.inLayer))
    {
        return false;
    }

    return other.collidesWithSquare(*this);
}

bool CollisionShapeSquare::collidesWithSquare(const CollisionShapeSquare &square) const
{
    const Vector position = getGlobalPosition();
    const Vector otherPosition = square.getGlobalPosition();

    return position.x + size.x > otherPosition.x &&
           position.x < otherPosition.x + square.size.x &&
           position.y + size.y > otherPosition.y &&
           position.y < otherPosition.y + square.size.y;
}

Vector CollisionShapeSquare::getCollisionNormal(const CollisionShape &other) const
{
    return other.getCollisionNormalSquare(*this);
}

Vector CollisionShapeSquare::getCollisionNormalSquare(const class CollisionShapeSquare &square) const
{
    const Vector position = getGlobalPosition();

    Vector center = position + size / 2;

    const Vector otherPosition = square.getGlobalPosition();

    Vector otherCenter = otherPosition + square.size / 2;

    Vector normal = (otherCenter - center).normalize();

    return normal;
}
