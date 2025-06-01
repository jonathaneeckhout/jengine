#include <gtest/gtest.h>
#include "jengine/core/Game.hpp"
#include "jengine/basics/Object.hpp"

// Define a fake Object for rootObject testing
class FakeObject : public Object
{
public:
    int inputCalls = 0, updateCalls = 0, outputCalls = 0, deleteCheckCalls = 0;

    void input() override { inputCalls++; }
    void update(float) override { updateCalls++; }
    void output() override { outputCalls++; }
};

TEST(GameTest, SingletonCreationAndDeletion)
{
    Game *game1 = Game::getInstance();
    Game *game2 = Game::getInstance();

    EXPECT_EQ(game1, game2);

    Game::deleteInstance();
    EXPECT_EQ(Game::getInstance() != nullptr, true);

    Game::deleteInstance(); // Clean up again
}

TEST(GameTest, SetFPSUpdatesValue)
{
    Game *game = Game::getInstance();
    game->setFPS(120.0f);

    Game::deleteInstance();
}

TEST(GameTest, SetRootObjectAndInvokeInputCallsFake)
{
    FakeObject *fake = new FakeObject();
    Game *game = Game::getInstance();
    game->setRootObject(fake);

    game->__tick(1.0f);

    EXPECT_EQ(fake->inputCalls, 1);

    Game::deleteInstance();
}

TEST(GameTest, UpdateCallsRootObjectUpdate)
{
    FakeObject *fake = new FakeObject();
    Game *game = Game::getInstance();
    game->setRootObject(fake);

    game->__tick(1.0f);

    EXPECT_EQ(fake->updateCalls, 1);

    Game::deleteInstance();
}

TEST(GameTest, OutputCallsRootObjectOutput)
{
    FakeObject *fake = new FakeObject();
    Game *game = Game::getInstance();
    game->setRootObject(fake);

    game->__tick(1.0f);

    EXPECT_EQ(fake->outputCalls, 1);

    Game::deleteInstance();
}

TEST(GameTest, QueueDeleteIsTriggered)
{
    Game *game = Game::getInstance();
    Object *root = new Object();

    Object *parent = new Object();

    Object *child = new Object();

    parent->addChild(child);

    root->addChild(parent);

    game->setRootObject(root);

    EXPECT_EQ(root->getChildren().size(), 1);

    parent->queueDelete();

    game->__tick(1.0f);

    EXPECT_EQ(root->getChildren().size(), 0);

    game->__tick(1.0f);

    EXPECT_EQ(root->getChildren().size(), 0);

    Game::deleteInstance();
}
