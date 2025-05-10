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

class Game : public Object
{

public:
    ~Game();

    // Delete copy constructor
    Game(const Game &) = delete;

    // Init function must be called after the game instance exists
    void init();

    // Cleanup function must be called before the game instance is deleted
    void cleanup();

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

    // Todo: populate this map when objects are added as childs to the game object
    std::unordered_map<std::string, Object *> objects;

    std::vector<Object *> toBedeleted = {};

    Game();

    void input() override;
    void update(float dt) override;
    void output() override;
};