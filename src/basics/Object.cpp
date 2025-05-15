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
            child->cleanup();
    }
}

const std::string &Object::getId() const { return id; }

Object *Object::getParent() const { return parent; }

std::vector<Object *> Object::getChildren() const
{
    std::vector<Object *> result;
    result.reserve(children.size());
    for (const auto &c : children)
    {
        result.push_back(c.get());
    }
    return result;
}

Object *Object::getChild(const std::string &childID)
{
    auto it = std::find_if(children.begin(), children.end(), [&](const std::unique_ptr<Object> &entry)
                           { return entry && entry->getId() == childID; });

    return (it != children.end()) ? it->get() : nullptr;
}

Object *Object::getChildByName(const std::string &searchName)
{
    for (const auto &child : children)
    {
        if (child && child->name == searchName)
        {
            return child.get();
        }
    }

    return nullptr;
}

bool Object::addChild(std::unique_ptr<Object> child)
{
    if (!child)
    {
        return false;
    }

    if (getChild(child->getId()) != nullptr)
    {
        return false;
    }

    child->parent = this;

    children.push_back(std::move(child));

    return true;
}

bool Object::removeChild(Object *childPtr)
{
    if (!childPtr)
    {
        return false;
    }

    auto it = std::find_if(children.begin(), children.end(), [&](const std::unique_ptr<Object> &entry)
                           { return entry.get() == childPtr; });

    if (it == children.end())
    {
        return false;
    }

    (*it)->parent = nullptr;

    children.erase(it);

    return true;
}

void Object::queueDelete()
{
    if (auto *game = Game::getInstance())
    {
        game->queueDeleteObject(this);
    }
}

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

void Object::input() {}
void Object::update(float) {}
void Object::output() {}
void Object::cleanup() {}
