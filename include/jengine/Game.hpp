#pragma once
#include <atomic>
#include <string>

#include "jengine/Object.hpp"
#include "jengine/Renderer.hpp"
#include "jengine/Controls.hpp"
#include "jengine/Resources.hpp"

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

private:
    static Game *instancePtr;

    float fps = 30.0f;

    std::atomic<bool> running;

    Renderer *renderer = NULL;
    Controls *controls = NULL;
    Resources *resources = NULL;

    Game();

    void input() override;
    void update(float dt) override;
    void output() override;
};