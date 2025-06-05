#include <algorithm>

#include "jengine/basics/Object.hpp"
#include "jengine/utils/uuid.hpp"
#include "jengine/core/Game.hpp"

Object::Object() : id(jengine::utils::generate_uuid())
{
    events.createEvent<>("onDeleted");
}

Object::~Object()
{
    for (auto &child : children)
    {
        delete child;
    }
}

Object *Object::getChild(const std::string &childID)
{
    for (auto child : children)
    {
        if (child->getId() == childID)
        {
            return child;
        }
    }

    return nullptr;
}

Object *Object::getChild(const unsigned int index)
{
    if (index < children.size())
    {
        return children[index];
    }

    return nullptr;
}

Object *Object::getChildByName(const std::string &searchName)
{
    for (const auto &child : children)
    {
        if (child && child->name == searchName)
        {
            return child;
        }
    }

    return nullptr;
}

bool Object::addChild(Object *child)
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

    if (isPartOfGame())
    {
        child->__addToGame();
    }

    children.push_back(std::move(child));

    return true;
}

Object *Object::removeChild(Object *child)
{
    if (!child)
    {
        return nullptr;
    }

    auto it = std::find_if(children.begin(), children.end(),
                           [&](Object *entry)
                           {
                               return entry && entry->getId() == child->getId();
                           });

    if (it == children.end())
    {
        return nullptr;
    }

    Object *removed = *it;

    removed->__removeFromGame();
    removed->parent = nullptr;

    children.erase(it);

    return removed;
}

void Object::queueDelete()
{
    shouldDelete = true;
}

void Object::__addToGame()
{
    partOfGame = true;

    for (const auto &child : children)
    {
        child->__addToGame();
    }
}

void Object::__removeFromGame()
{
    partOfGame = false;

    for (const auto &child : children)
    {
        child->__removeFromGame();
    }
}

void Object::__cleanup()
{
    cleanup();

    events.trigger("onDeleted");
}

void Object::__input()
{
    input();

    events.processAll();

    for (const auto &child : children)
    {
        child->__input();
    }
}

void Object::__update(float dt)
{
    update(dt);

    for (const auto &child : children)
    {
        child->__update(dt);
    }
}

void Object::__sync(bool shouldDirty)
{
    dirty |= shouldDirty;

    sync(dirty);

    for (const auto &child : children)
    {
        child->__sync(dirty);
    }
}

void Object::__physics(float dt)
{
    physics(dt);

    for (const auto &child : children)
    {
        child->__physics(dt);
    }
}

void Object::__output()
{
    if (!visible)
    {
        return;
    }

    output();

    for (const auto &child : children)
    {
        child->__output();
    }
}

void Object::__checkDeleteObjects()
{
    std::vector<Object *> toDelete;

    for (auto child : children)
    {

        if (child->__queuedForDeletion())
        {
            toDelete.push_back(child);
        }
        else
        {
            child->__checkDeleteObjects();
        }
    }

    for (Object *child : toDelete)
    {
        removeChild(child);

        child->__cleanup();

        delete child;

        child = nullptr;
    }
}
