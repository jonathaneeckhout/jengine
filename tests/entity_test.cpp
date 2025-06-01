#include <gtest/gtest.h>
#include "jengine/entities/Entity.hpp"

TEST(EntityTest, DefaultConstructorInitializesToZero)
{
    Entity e;
    EXPECT_EQ(e.getPosition(), Vector(0, 0));
    EXPECT_EQ(e.getGlobalPosition(), Vector(0, 0));
}

TEST(EntityTest, PositionConstructorSetsLocalAndGlobal)
{
    Entity e(Vector(10, 20));
    EXPECT_EQ(e.getPosition(), Vector(10, 20));
    EXPECT_EQ(e.getGlobalPosition(), Vector(10, 20));
}

TEST(EntityTest, PositionVelocityConstructorSetsCorrectly)
{
    Entity e(Vector(3, 4), Vector(1, 2));
    EXPECT_EQ(e.getPosition(), Vector(3, 4));
    EXPECT_EQ(e.getGlobalPosition(), Vector(3, 4));
}

TEST(EntityTest, SetPositionUpdatesGlobalPosition)
{
    Entity e(Vector(5, 5));
    e.setPosition(Vector(10, 10));
    EXPECT_EQ(e.getPosition(), Vector(10, 10));
    EXPECT_EQ(e.getGlobalPosition(), Vector(10, 10));
}

TEST(EntityTest, SetGlobalPositionOverridesGlobal)
{
    Entity e(Vector(1, 2));
    e.setGlobalPosition(Vector(100, 200));
    EXPECT_EQ(e.getGlobalPosition(), Vector(100, 200));
}

TEST(EntityTest, ChildEntityGlobalPositionIsRelativeToParent)
{
    Entity *parent = new Entity(Vector(10, 10));
    Entity *child = new Entity(Vector(5, 5));

    parent->addChild(child);

    EXPECT_EQ(child->getPosition(), Vector(5, 5));
    EXPECT_EQ(child->getGlobalPosition(), Vector(15, 15));

    delete parent;
}

TEST(EntityTest, NestedChildGlobalPositionIsRecursive)
{
    Entity *root = new Entity(Vector(1, 1));
    Entity *mid = new Entity(Vector(2, 2));
    Entity *leaf = new Entity(Vector(3, 3));

    root->addChild(mid);
    mid->addChild(leaf);

    EXPECT_EQ(leaf->getGlobalPosition(), Vector(6, 6)); // 1 + 2 + 3

    delete root;
}

TEST(EntityTest, UpdatingParentPositionUpdatesChildGlobalPosition)
{
    Entity *parent = new Entity(Vector(10, 10));
    Entity *child = new Entity(Vector(5, 5));

    parent->addChild(child);
    parent->setPosition(Vector(20, 20));

    EXPECT_EQ(child->getGlobalPosition(), Vector(25, 25));

    delete parent;
}
