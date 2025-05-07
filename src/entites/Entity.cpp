#include "jengine/entities/Entity.hpp"

Entity::Entity() {}

Entity::Entity(Vector position) : position(position) {}

Entity::~Entity() {}

void Entity::__update(float dt)
{
    Object::__update(dt);

    if (Entity *parentEntity = dynamic_cast<Entity *>(getParent()))
    {
        globalPosition = parentEntity->globalPosition + position;
    }
    else
    {
        globalPosition = position;
    }
}