#pragma once

#include <string>
#include <vector>

class Object
{
public:
    std::string name = "";

    Object();

    virtual ~Object();

    const std::string &getId() const;

    Object *getParent() const;

    std::vector<Object *> &getChildren();

    Object *getChild(const std::string &id);

    Object *getChildByName(const std::string &name);

    virtual bool addChild(Object *object);

    bool removeChild(const std::string &id);

    bool deleteChild(const std::string &id);

    void deleteChildren();

    void queueDelete();

    // Don't override, only for internal usage.
    void __input();

    // Don't override, only for internal usage.
    void __update(float dt);

    // Don't override, only for internal usage.
    void __output();

protected:
    virtual void input();

    virtual void update(float dt);

    virtual void output();

private:
    std::string id = "";

    Object *parent = nullptr;

    std::vector<Object *> children;
};