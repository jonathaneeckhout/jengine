#pragma once

#include <string>
#include <vector>

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
    Object *getChildByName(const std::string &name);

    virtual bool addChild(Object *child);
    Object *removeChild(Object *child);

    void queueDelete();

    virtual void __addToGame();
    virtual void __removeFromGame();

    bool isPartOfGame() { return partOfGame; };

    virtual void __init() { init(); };
    virtual void __cleanup() { cleanup(); };

    void __input();
    void __update(float dt);
    void __output();
    void __checkDeleteObjects();
    bool __queuedForDeletion() { return shouldDelete; };

    void setVisible(bool value) { visible = value; };
    bool isVisible() { return visible; };

protected:
    Object *parent = nullptr;
    std::vector<Object *> children;

    bool visible = true;

    virtual void init() {};
    virtual void cleanup() {};

    virtual void input() {};
    virtual void update(float) {};
    virtual void output() {};

private:
    std::string id = "";
    std::string name = "";
    bool partOfGame = false;
    bool shouldDelete = false;
};