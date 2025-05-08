#include "jengine/entities/Entity.hpp"

Entity::Entity() {}

Entity::Entity(Vector position) : position(position) {}

Entity::~Entity() {}

Vector Entity::getPosition()
{
    return position;
}

void Entity::setPosition(Vector newPosition)
{
    position = newPosition;

    __update_global_position();
}

Vector Entity::getGlobalPosition()
{
    return globalPosition;
}

void Entity::setGlobalPosition(Vector newPosition)
{
    globalPosition = newPosition;
}

void Entity::__update_global_position()
{
    if (Entity *parentEntity = dynamic_cast<Entity *>(getParent()))
    {
        globalPosition = parentEntity->globalPosition + position;
    }
    else
    {
        globalPosition = position;
    }

    for (auto &child : getChildren())
    {
        if (Entity *childEntity = dynamic_cast<Entity *>(child))
        {
            childEntity->__update_global_position();
        }
    }
}