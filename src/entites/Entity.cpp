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
    if (auto parentShared = parent.lock())
    {
        if (Entity *parentEntity = dynamic_cast<Entity *>(parentShared.get()))
        {
            globalPosition = parentEntity->globalPosition + position;
        }
        else
        {
            globalPosition = position;
        }
    }
    else
    {
        globalPosition = position;
    }

    for (const auto &child : children)
    {
        if (!child)
            continue;

        if (Entity *childEntity = dynamic_cast<Entity *>(child.get()))
        {
            childEntity->__update_global_position();
        }
    }
}

bool Entity::addChild(std::shared_ptr<Object> child)
{
    if (!Object::addChild(child))
    {
        return false;
    }

    __update_global_position();

    return true;
}