#include "jengine/entities/Entity.hpp"

Entity::Entity() {}

Entity::Entity(Vector position) : position(position), globalPosition(position) {}

Entity::Entity(Vector position, Vector velocity) : velocity(velocity), position(position), globalPosition(position) {}

Entity::~Entity() {}

void Entity::setPosition(Vector newPosition)
{
    position = newPosition;

    __update_global_position();
}

void Entity::__update_global_position()
{
    if (parent != nullptr)
    {
        if (Entity *parentEntity = dynamic_cast<Entity *>(parent))
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