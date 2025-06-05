#pragma once

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

#include "jengine/basics/Events.hpp"

class Object
{
public:
    Object();
    virtual ~Object();

    const std::string &getId() const { return id; };

    const std::string &getName() const { return name; }
    void setName(const std::string &newName) { name = newName; }

    Object *getParent() const { return parent; };

    const std::vector<Object *> &getChildren() const { return children; };
    std::size_t getChildrenSize() { return children.size(); };

    Object *getChild(const std::string &childID);
    Object *getChild(const unsigned int index);

    template <typename T>
    T *getChild()
    {
        for (auto *child : children)
        {
            if (auto *casted = dynamic_cast<T *>(child))
            {
                return casted;
            }
        }
        return nullptr;
    }

    Object *getChildByName(const std::string &name);

    virtual bool addChild(Object *child);
    Object *removeChild(Object *child);

    void queueDelete();

    virtual void __addToGame();
    virtual void __removeFromGame();

    bool isPartOfGame() { return partOfGame; };

    virtual void __init() { init(); };
    virtual void __cleanup();

    void __input();
    void __update(float dt);
    void __sync(bool shouldDirty);
    void __physics(float dt);
    void __output();

    void __checkDeleteObjects();
    bool __queuedForDeletion() { return shouldDelete; };

    void setVisible(bool value) { visible = value; };
    bool isVisible() { return visible; };

    template <typename... Args>
    int addEventHandler(const std::string &name, const std::function<void(Args...)> &handler)
    {
        return events.addHandler<Args...>(name, handler);
    }

    void removeEventHandler(const std::string &name, int handlerId)
    {
        events.removeHandler(name, handlerId);
    }

protected:
    Events events;
    bool visible = true;
    bool dirty = true;

    virtual void init() {};
    virtual void cleanup() {};

    virtual void input() {};
    virtual void update(float) {};
    virtual void sync(bool) {};
    virtual void physics(float) {};
    virtual void output() {};

private:
    std::string id = "";
    std::string name = "";

    Object *parent = nullptr;

    std::vector<Object *> children;

    bool partOfGame = false;
    bool shouldDelete = false;
};