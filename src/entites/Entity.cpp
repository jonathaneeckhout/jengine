#include "jengine/entities/Entity.hpp"

Entity::Entity() {}

Entity::Entity(Vector position) : position(position)
{
    __update_global_position();
}

Entity::Entity(Vector position, Vector velocity) : velocity(velocity), position(position)
{
    __update_global_position();
}

Entity::~Entity() {}

Vector Entity::getPosition() const
{
    return position;
}

void Entity::setPosition(Vector newPosition)
{
    position = newPosition;

    __update_global_position();
}

Vector Entity::getGlobalPosition() const
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

bool Entity::addChild(Object *child)
{
    if (!Object::addChild(child))
    {
        return false;
    }

    __update_global_position();

    return true;
}