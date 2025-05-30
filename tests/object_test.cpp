#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "jengine/basics/Object.hpp"

class TestableObject : public Object
{
public:
    bool initialized = false;
    bool cleanedUp = false;
    bool updated = false;
    float lastDelta = 0.0f;

    void init() override { initialized = true; }
    void cleanup() override { cleanedUp = true; }
    void update(float dt) override
    {
        updated = true;
        lastDelta = dt;
    }
};

TEST(ObjectTest, GeneratesUniqueId)
{
    auto obj1 = std::make_shared<Object>();
    auto obj2 = std::make_shared<Object>();

    EXPECT_FALSE(obj1->getId().empty());
    EXPECT_FALSE(obj2->getId().empty());
    EXPECT_NE(obj1->getId(), obj2->getId());
}

TEST(ObjectTest, AddChildSetsParent)
{
    auto parent = std::make_shared<Object>();
    auto child = std::make_shared<Object>();

    EXPECT_TRUE(parent->addChild(child));
    EXPECT_EQ(child->getParent().lock(), parent);
    EXPECT_EQ(parent->getChildren().size(), 1);
}

TEST(ObjectTest, AddDuplicateChildFails)
{
    auto parent = std::make_shared<Object>();
    auto child = std::make_shared<Object>();

    EXPECT_TRUE(parent->addChild(child));
    EXPECT_FALSE(parent->addChild(child));
}

TEST(ObjectTest, RemoveChildWorksCorrectly)
{
    auto parent = std::make_shared<Object>();
    // First reference to child
    auto child = std::make_shared<Object>();

    // Second reference to child (inside parent children list)
    parent->addChild(child);
    EXPECT_EQ(child.use_count(), 2);

    // Second reference passed from parent to removed
    auto removed = parent->removeChild(child.get());

    EXPECT_EQ(removed, child);
    EXPECT_EQ(parent->getChildren().size(), 0);
    EXPECT_TRUE(child->getParent().expired());

    // There should be only 2 references
    EXPECT_EQ(child.use_count(), 2);
}

TEST(ObjectTest, GetChildById)
{
    auto parent = std::make_shared<Object>();
    auto child = std::make_shared<Object>();

    parent->addChild(child);
    auto retrieved = parent->getChild(child->getId()).lock();

    EXPECT_EQ(retrieved, child);
}

TEST(ObjectTest, GetChildByName)
{
    auto parent = std::make_shared<Object>();
    auto child = std::make_shared<Object>();
    child->setName("Hero");

    parent->addChild(child);
    auto retrieved = parent->getChildByName("Hero").lock();

    EXPECT_EQ(retrieved, child);
}

TEST(ObjectTest, GetChildByNonExistingName)
{
    auto parent = std::make_shared<Object>();
    auto child = std::make_shared<Object>();
    child->setName("Hero");

    parent->addChild(child);
    auto retrieved = parent->getChildByName("NotYourHero").lock();

    EXPECT_EQ(retrieved, nullptr);
}

TEST(ObjectTest, QueueDeleteMarksObjectForDeletion)
{
    auto obj = std::make_shared<Object>();
    EXPECT_FALSE(obj->__queuedForDeletion());

    obj->queueDelete();
    EXPECT_TRUE(obj->__queuedForDeletion());
}

TEST(ObjectTest, InitAndCleanupCalled)
{
    auto obj = std::make_shared<TestableObject>();

    obj->__init();
    EXPECT_TRUE(obj->initialized);

    obj->__cleanup();
    EXPECT_TRUE(obj->cleanedUp);
}

TEST(ObjectTest, UpdateCalledWithDeltaTime)
{
    auto obj = std::make_shared<TestableObject>();

    obj->__update(0.16f);
    EXPECT_TRUE(obj->updated);
    EXPECT_FLOAT_EQ(obj->lastDelta, 0.16f);
}

TEST(ObjectTest, CheckDeleteCleansUpAndRemovesChild)
{
    auto parent = std::make_shared<Object>();
    auto child = std::make_shared<TestableObject>();

    parent->addChild(child);
    child->queueDelete();

    EXPECT_EQ(parent->getChildren().size(), 1);
    parent->__checkDeleteObjects();
    EXPECT_EQ(parent->getChildren().size(), 0);
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
    auto parent = std::make_shared<Object>();
    auto child = std::make_shared<Object>();

    parent->addChild(child);

    parent->__addToGame();

    EXPECT_TRUE(parent->isPartOfGame());
    EXPECT_TRUE(child->isPartOfGame());
}

TEST(ObjectTest, RemoveFromGamePropagatesToChildren)
{
    auto parent = std::make_shared<Object>();
    auto child = std::make_shared<Object>();

    parent->addChild(child);
    parent->__addToGame();

    parent->__removeFromGame();

    EXPECT_FALSE(parent->isPartOfGame());
    EXPECT_FALSE(child->isPartOfGame());
}