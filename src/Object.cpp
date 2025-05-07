#include <algorithm>

#include "jengine/Object.hpp"
#include "jengine/utils/uuid.hpp"

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

    children.erase(it);
    return true;
}

bool Object::deleteChild(const std::string &id)
{
    auto it = std::find_if(children.begin(), children.end(),
                           [&](Object *child)
                           {
                               return child && child->id == id; // or child->getId()
                           });

    if (it == children.end())
    {
        return false;
    }

    delete *it;         // Free the memory
    children.erase(it); // Remove from vector
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

void Object::__input()
{
    for (auto &child : children)
    {
        child->__input();
    }

    input();
}

void Object::__update(float dt)
{
    for (auto &child : children)
    {
        child->__update(dt);
    }

    update(dt);
}

void Object::__output()
{
    for (auto &child : children)
    {
        child->__output();
    }

    output();
}

void Object::input() {}

void Object::update(float) {}

void Object::output() {}
