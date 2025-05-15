#include <algorithm>

#include "jengine/basics/Object.hpp"
#include "jengine/utils/uuid.hpp"
#include "jengine/core/Game.hpp"

Object::Object() : id(generate_uuid()) {}

Object::~Object()
{
    for (auto &child : children)
    {
        if (child)
        {
            child->__cleanup();
        }
    }
}

const std::string &Object::getId() const { return id; }

std::weak_ptr<Object> Object::getParent() const { return parent; }

std::vector<std::weak_ptr<Object>> Object::getChildren() const
{
    std::vector<std::weak_ptr<Object>> result;

    result.reserve(children.size());

    for (const auto &c : children)
    {
        result.push_back(c);
    }

    return result;
}

std::weak_ptr<Object> Object::getChild(const std::string &childID)
{
    auto it = std::find_if(children.begin(), children.end(), [&](const std::shared_ptr<Object> &entry)
                           { return entry && entry->getId() == childID; });

    return (it != children.end()) ? *it : std::weak_ptr<Object>{};
}

std::weak_ptr<Object> Object::getChildByName(const std::string &searchName)
{
    for (const auto &child : children)
    {
        if (child && child->name == searchName)
        {
            return child;
        }
    }

    return std::weak_ptr<Object>{};
}

bool Object::addChild(std::shared_ptr<Object> child)
{
    if (!child)
    {
        return false;
    }

    if (!getChild(child->getId()).expired())
    {
        return false;
    }

    child->parent = shared_from_this();

    children.push_back(std::move(child));

    return true;
}

std::shared_ptr<Object> Object::removeChild(Object *childPtr)
{
    if (!childPtr)
    {
        return nullptr;
    }

    auto it = std::find_if(children.begin(), children.end(),
                           [&](const std::shared_ptr<Object> &entry)
                           {
                               return entry.get() == childPtr;
                           });

    if (it == children.end())
    {
        return nullptr;
    }

    (*it)->parent.reset();

    std::shared_ptr<Object> removedChild = std::move(*it);

    children.erase(it);

    return removedChild;
}

void Object::queueDelete()
{
    shouldDelete = true;
}

void Object::__init() {}

void Object::__cleanup() {}

void Object::__input()
{
    input();

    for (const auto &child : children)
    {
        if (child)
        {
            child->__input();
        }
    }
}

void Object::__update(float dt)
{
    update(dt);

    for (const auto &child : children)
    {
        if (child)
        {
            child->__update(dt);
        }
    }
}

void Object::__output()
{
    output();

    for (const auto &child : children)
    {
        if (child)
        {
            child->__output();
        }
    }
}

void Object::__checkDeleteObjects()
{
    for (const auto &child : children)
    {
        if (child)
        {
            if (child->__queuedForDeletion()) {
                removeChild(child.get());
            } else {
                child->__checkDeleteObjects();
            }
        }
    }
}

bool Object::__queuedForDeletion()
{
    return shouldDelete;
}

void Object::input() {}
void Object::update(float) {}
void Object::output() {}
