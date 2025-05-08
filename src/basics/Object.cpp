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
        delete child;
    }
}

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

Object *Object::getChild(const std::string &id)
{
    for (auto &child : children)
    {
        if (child->id == id)
        {
            return child;
        }
    }

    return nullptr;
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

bool Object::addChild(Object *object)
{
    if (getChild(object->getId()) != nullptr)
    {
        return false;
    }

    object->parent = this;

    children.push_back(object);

    return true;
}

bool Object::removeChild(const std::string &id)
{
    auto it = std::find_if(children.begin(), children.end(),
                           [&](Object *child)
                           {
                               return child && child->id == id;
                           });

    if (it == children.end())
    {
        return false;
    }

    (*it)->parent = nullptr;

    children.erase(it);
    return true;
}

bool Object::deleteChild(const std::string &id)
{
    auto it = std::find_if(children.begin(), children.end(),
                           [&](Object *child)
                           {
                               return child && child->id == id;
                           });

    if (it == children.end())
    {
        return false;
    }

    delete *it;

    children.erase(it);

    return true;
}

void Object::deleteChildren()
{
    for (Object *child : children)
    {
        delete child;
    }
    children.clear();
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
