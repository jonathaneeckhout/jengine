#include <gtest/gtest.h>
#include <string>
#include "jengine/basics/Object.hpp"

class TestableObject : public Object
{
public:
    bool updated = false;
    float lastDelta = 0.0f;

    void update(float dt) override
    {
        updated = true;
        lastDelta = dt;
    }
};

TEST(ObjectTest, GeneratesUniqueId)
{
    Object *obj1 = new Object();
    Object *obj2 = new Object();

    EXPECT_FALSE(obj1->getId().empty());
    EXPECT_FALSE(obj2->getId().empty());
    EXPECT_NE(obj1->getId(), obj2->getId());

    delete obj1;
    delete obj2;
}

TEST(ObjectTest, AddChildSetsParent)
{
    Object *parent = new Object();
    Object *child = new Object();

    EXPECT_TRUE(parent->addChild(child));
    EXPECT_EQ(child->getParent(), parent);
    EXPECT_EQ(parent->getChildren().size(), 1);

    delete parent;
}

TEST(ObjectTest, AddDuplicateChildFails)
{
    Object *parent = new Object();
    Object *child = new Object();

    EXPECT_TRUE(parent->addChild(child));
    EXPECT_FALSE(parent->addChild(child));

    delete parent;
}

TEST(ObjectTest, RemoveChildWorksCorrectly)
{
    Object *parent = new Object();
    Object *child = new Object();

    parent->addChild(child);
    Object *removed = parent->removeChild(child);

    EXPECT_EQ(removed, child);
    EXPECT_EQ(parent->getChildren().size(), 0);
    EXPECT_EQ(child->getParent(), nullptr);

    delete child;
    delete parent;
}

TEST(ObjectTest, GetChildById)
{
    Object *parent = new Object();
    Object *child = new Object();

    parent->addChild(child);
    Object *retrieved = parent->getChild(child->getId());

    EXPECT_EQ(retrieved, child);

    delete parent;
}

TEST(ObjectTest, GetChildByName)
{
    Object *parent = new Object();
    Object *child = new Object();
    child->setName("Hero");

    parent->addChild(child);
    Object *retrieved = parent->getChildByName("Hero");

    EXPECT_EQ(retrieved, child);

    delete parent;
}

TEST(ObjectTest, GetChildByNonExistingName)
{
    Object *parent = new Object();
    Object *child = new Object();
    child->setName("Hero");

    parent->addChild(child);
    Object *retrieved = parent->getChildByName("NotYourHero");

    EXPECT_EQ(retrieved, nullptr);

    delete parent;
}

TEST(ObjectTest, QueueDeleteMarksObjectForDeletion)
{
    Object *obj = new Object();
    EXPECT_FALSE(obj->__queuedForDeletion());

    obj->queueDelete();
    EXPECT_TRUE(obj->__queuedForDeletion());

    delete obj;
}

TEST(ObjectTest, UpdateCalledWithDeltaTime)
{
    TestableObject *obj = new TestableObject();

    obj->__update(0.16f);
    EXPECT_TRUE(obj->updated);
    EXPECT_FLOAT_EQ(obj->lastDelta, 0.16f);

    delete obj;
}

TEST(ObjectTest, CheckDeleteCleansUpAndRemovesChild)
{
    Object *parent = new Object();
    TestableObject *child = new TestableObject();

    parent->addChild(child);
    child->queueDelete();

    EXPECT_EQ(parent->getChildren().size(), 1);
    parent->__checkDeleteObjects();
    EXPECT_EQ(parent->getChildren().size(), 0);

    delete parent;
}

TEST(ObjectTest, AddToGameSetsFlag)
{
    Object obj;
    EXPECT_FALSE(obj.isPartOfGame());

    obj.__addToGame();

    EXPECT_TRUE(obj.isPartOfGame());
}

TEST(ObjectTest, RemoveFromGameUnsetsFlag)
{
    Object obj;
    obj.__addToGame();
    ASSERT_TRUE(obj.isPartOfGame());

    obj.__removeFromGame();

    EXPECT_FALSE(obj.isPartOfGame());
}

TEST(ObjectTest, AddToGamePropagatesToChildren)
{
    Object *parent = new Object();
    Object *child = new Object();

    parent->addChild(child);
    parent->__addToGame();

    EXPECT_TRUE(parent->isPartOfGame());
    EXPECT_TRUE(child->isPartOfGame());

    delete parent;
}

TEST(ObjectTest, RemoveFromGamePropagatesToChildren)
{
    Object *parent = new Object();
    Object *child = new Object();

    parent->addChild(child);
    parent->__addToGame();

    parent->__removeFromGame();

    EXPECT_FALSE(parent->isPartOfGame());
    EXPECT_FALSE(child->isPartOfGame());

    delete parent;
}
