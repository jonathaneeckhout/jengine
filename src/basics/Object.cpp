#include <algorithm>

#include "jengine/basics/Object.hpp"
#include "jengine/utils/uuid.hpp"
#include "jengine/core/Game.hpp"

Object::Object()
{
    id = generate_uuid();
};

Object::~Object()
{
    for (auto &child : children)
    {
        DeleteObject(child);
    }
}

bool Object::DeleteObject(Object *object)
{
    if (object == nullptr)
    {
        return false;
    }

    object->cleanup();

    delete object;

    return true;
}

void Object::cleanup() {}

const std::string &Object::getId() const
{
    return id;
}

Object *Object::getParent() const
{
    return parent;
}

std::vector<Object *> &Object::getChildren()
{
    return children;
}

Object *Object::getChild(const std::string &childID)
{
    auto it = std::find_if(children.begin(), children.end(),
                           [&](Object *entry)
                           {
                               return entry && entry->getId() == childID;
                           });

    if (it == children.end())
    {
        return nullptr;
    }

    return *it;
}

Object *Object::getChildByName(const std::string &name)
{
    for (auto &child : children)
    {
        if (child->name == name)
        {
            return child;
        }
    }

    return nullptr;
}

bool Object::addChild(Object *child)
{
    if (child == nullptr)
    {
        return false;
    }

    if (getChild(child->getId()) != nullptr)
    {
        return false;
    }

    child->parent = this;

    children.push_back(child);

    return true;
}

bool Object::removeChild(Object *child)
{
    if (child == nullptr)
    {
        return false;
    }

    auto it = std::find_if(children.begin(), children.end(),
                           [&](Object *entry)
                           {
                               return entry && entry->getId() == child->getId();
                           });

    if (it == children.end())
    {
        return false;
    }

    child->parent = nullptr;

    children.erase(it);

    return true;
}

void Object::queueDelete()
{
    Game *game = Game::getInstance();
    if (game == nullptr)
    {
        return;
    }

    game->queueDeleteObject(this);
}

void Object::__input()
{
    input();

    for (auto &child : children)
    {
        child->__input();
    }
}

void Object::__update(float dt)
{
    update(dt);

    for (auto &child : children)
    {
        child->__update(dt);
    }
}

void Object::__output()
{
    output();

    for (auto &child : children)
    {
        child->__output();
    }
}

void Object::input() {}

void Object::update(float) {}

void Object::output() {}
