#pragma once
#include <atomic>
#include <string>
#include <unordered_map>
#include <vector>
#include <deque>

#include "jengine/basics/Object.hpp"
#include "jengine/core/Physics.hpp"
#include "jengine/core/Renderer.hpp"
#include "jengine/core/Controls.hpp"
#include "jengine/core/Resources.hpp"

class Game
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
    void setRootObject(Object *object);

private:
    static Game *instancePtr;

    float fps = 30.0f;

    std::atomic<bool> running;

    Physics *phyics = nullptr;
    Renderer *renderer = nullptr;
    Controls *controls = nullptr;
    Resources *resources = nullptr;
    Object *rootObject = nullptr;

    std::vector<Object *> toBedeleted = {};

    Game();

    void input();
    void update(float dt);
    void output();
};