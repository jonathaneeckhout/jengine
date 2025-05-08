#pragma once
#include <atomic>
#include <string>
#include <vector>
#include <deque>

#include "jengine/basics/Object.hpp"
#include "jengine/core/Physics.hpp"
#include "jengine/core/Renderer.hpp"
#include "jengine/core/Controls.hpp"
#include "jengine/core/Resources.hpp"

class ToBeDeleted
{
public:
    std::string id = "";
    std::deque<std::string> parents = {};
};

class Game : public Object
{

public:
    ~Game();

    // Delete copy constructor
    Game(const Game &) = delete;

    static Game *getInstance();
    static void deleteInstance();

    void run();
    void stop();

    void queueDeleteObject(Object *object);

    void setFPS(float newFPS);

private:
    static Game *instancePtr;

    float fps = 30.0f;

    std::atomic<bool> running;

    Physics *phyics = nullptr;
    Renderer *renderer = nullptr;
    Controls *controls = nullptr;
    Resources *resources = nullptr;

    std::vector<ToBeDeleted *> toBedeleted = {};

    Game();

    void input() override;
    void update(float dt) override;
    void output() override;
};