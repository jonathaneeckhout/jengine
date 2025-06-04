#pragma once

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

#include "jengine/components/Component.hpp"

class Object
{
public:
    Object();
    virtual ~Object();

    const std::string &getId() const { return id; };

    const std::string &getName() const { return name; }
    void setName(const std::string &newName) { name = newName; }

    void addComponent(Component *component);

    Object *getParent() const { return parent; };

    template <typename T>
    T *getComponent()
    {
        for (auto *comp : components)
        {
            if (auto *casted = dynamic_cast<T *>(comp))
            {
                return casted;
            }
        }
        return nullptr;
    }

    const std::vector<Object *> &getChildren() const { return children; };
    std::size_t getChildrenSize() { return children.size(); };

    Object *getChild(const std::string &childID);
    Object *getChild(const unsigned int index);
    Object *getChildByName(const std::string &name);

    virtual bool addChild(Object *child);
    Object *removeChild(Object *child);

    void queueDelete();

    virtual void __addToGame();
    virtual void __removeFromGame();

    bool isPartOfGame() { return partOfGame; };

    virtual void __init() { init(); };
    virtual void __cleanup();

    void __update(float dt);
    void __sync(bool shouldDirty);
    void __output();
    void __checkDeleteObjects();
    bool __queuedForDeletion() { return shouldDelete; };

    void setVisible(bool value) { visible = value; };
    bool isVisible() { return visible; };

    int addDeleteHandler(std::function<void()> handler);
    void removeDeleteHandler(int id);

protected:
    bool visible = true;

    virtual void init() {};
    virtual void cleanup() {};

    virtual void update(float) {};
    virtual void sync(bool) {};
    virtual void output() {};

private:
    std::string id = "";
    std::string name = "";

    std::vector<Component *> components;

    Object *parent = nullptr;

    std::vector<Object *> children;

    bool dirty = true;

    bool partOfGame = false;
    bool shouldDelete = false;

    int nextdeleteHandlerId = 1;
    std::unordered_map<int, std::function<void()>> deleteHandlers;

    void invokeDeleteHandlers();
};