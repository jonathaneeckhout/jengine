#pragma once

class Object;

class Component
{
public:
    virtual ~Component() = default;

    virtual void update(float) {}
    virtual void sync(bool) {}
    virtual void output() {}
    virtual void onAddedToObject(Object *obj) { owner = obj; }

protected:
    Object *owner = nullptr;
    bool dirty = true;
};
