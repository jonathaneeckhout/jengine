#pragma once

#include <string>
#include <memory>
#include <vector>

class Object : public std::enable_shared_from_this<Object>
{
public:
    Object();
    virtual ~Object();

    const std::string &getId() const;
    const std::string &getName() const { return name; }
    void setName(const std::string &n) { name = n; }

    std::weak_ptr<Object> getParent() const;

    std::vector<std::weak_ptr<Object>> getChildren() const;
    std::weak_ptr<Object> getChild(const std::string &childID);
    std::weak_ptr<Object> getChildByName(const std::string &name);

    virtual bool addChild(std::shared_ptr<Object> child);
    std::shared_ptr<Object> removeChild(Object *child);

    void queueDelete();

    virtual void __init();
    virtual void __cleanup();

    void __input();
    void __update(float dt);
    void __output();
    void __checkDeleteObjects();
    bool __queuedForDeletion();

    static std::shared_ptr<Object> create()
    {
        auto obj = std::make_shared<Object>();
        obj->__init();

        return obj;
    }

protected:
    virtual void init();
    virtual void cleanup();

    virtual void input();
    virtual void update(float dt);
    virtual void output();

    std::weak_ptr<Object> parent;
    std::vector<std::shared_ptr<Object>> children;

private:
    std::string id;
    std::string name;
    bool shouldDelete = false;
};