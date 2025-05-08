#include "jengine/collision/CollisionShapeSquare.hpp"

CollisionShapeSquare::CollisionShapeSquare(Vector position, Vector size) : CollisionShape(position), size(size) {}

bool CollisionShapeSquare::collidesWith(const Vector &point) const
{

    const Vector position = getGlobalPosition();

    return point.x > position.x && point.x < position.x + size.x && point.y > position.y && point.y < position.y + size.y;
}

bool CollisionShapeSquare::collidesWith(const CollisionShapeSquare &other) const
{
    if (!(layer & other.layer))
    {
        return false;
    }

    const Vector position = getGlobalPosition();
    const Vector otherPosition = other.getGlobalPosition();

    return position.x + size.x > otherPosition.x &&
           position.x < otherPosition.x + other.size.x &&
           position.y + size.y > otherPosition.y &&
           position.y < otherPosition.y + other.size.y;
}