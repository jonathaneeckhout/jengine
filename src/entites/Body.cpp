#include "jengine/entities/Body.hpp"
#include "jengine/core/Physics.hpp"

Body::Body() {}

Body::Body(Vector position) : Entity(position) {}

Body::Body(Vector position, Vector velocity) : Entity(position, velocity) {}

Body::~Body() {}

void Body::moveAndSlide(float dt)
{
    if (collisionShape == nullptr)
    {
        setPosition(getPosition() + velocity * dt);

        return;
    }
}

void Body::moveAndStop(float dt)
{
    Vector newPosition = getPosition() + velocity * dt;

    if (collisionShape == nullptr)
    {
        setPosition(newPosition);

        return;
    }

    // Cache the old position
    Vector oldPosition = getPosition();

    // Try setting the new position
    setPosition(newPosition);

    // Set back the old position if the object collides with others
    Physics *physics = Physics::getInstance();
    if (physics->checkCollision(*collisionShape).size() > 0)
    {
        setPosition(oldPosition);
    }
}