#pragma once

class Object;

class Component
{
public:
    virtual ~Component() = default;

    virtual void update(float) {}
    virtual void sync(bool) {}
    virtual void physics(float) {}
    virtual void output() {}
    virtual void onAddedToObject(Object *obj) { owner = obj; }

    virtual void addToGame() {};
    virtual void removeFromGame() {};

protected:
    Object *owner = nullptr;
    bool dirty = true;
};
