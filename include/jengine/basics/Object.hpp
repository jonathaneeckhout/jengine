#pragma once

#include <string>
#include <vector>

class Object
{
public:
    static bool DeleteObject(Object *object);

    std::string name = "";

    Object();

    const std::string &getId() const;

    Object *getParent() const;

    std::vector<Object *> &getChildren();

    Object *getChild(const std::string &childID);

    Object *getChildByName(const std::string &childName);

    virtual bool addChild(Object *child);

    bool removeChild(Object *child);

    void queueDelete();

    // Don't override, only for internal usage.
    void __input();

    // Don't override, only for internal usage.
    void __update(float dt);

    // Don't override, only for internal usage.
    void __output();

protected:
    virtual ~Object();

    // This function is called right before the destructor
    virtual void cleanup();

    virtual void input();

    virtual void update(float dt);

    virtual void output();

private:
    std::string id = "";

    Object *parent = nullptr;

    std::vector<Object *> children;
};