#pragma once

#include <string>
#include <memory>
#include <vector>

class Object
{
public:
    Object();
    virtual ~Object();

    const std::string &getId() const;
    const std::string &getName() const { return name; }
    void setName(const std::string &n) { name = n; }

    Object *getParent() const;

    std::vector<Object *> getChildren() const;
    Object *getChild(const std::string &childID);
    Object *getChildByName(const std::string &name);

    virtual bool addChild(std::unique_ptr<Object> child);
    bool removeChild(Object *child);

    void queueDelete();

    void __input();
    void __update(float dt);
    void __output();

    virtual void cleanup();

protected:
    virtual void input();
    virtual void update(float dt);
    virtual void output();

private:
    std::string id;
    std::string name;
    Object *parent = nullptr;
    std::vector<std::unique_ptr<Object>> children;
};