#pragma once

#include <atomic>
#include <string>
#include <random>
#include <ctime>

#include "jengine/basics/Object.hpp"
#include "jengine/core/Physics.hpp"
#include "jengine/core/Renderer.hpp"
#include "jengine/core/Mixer.hpp"
#include "jengine/core/Controls.hpp"
#include "jengine/core/Resources.hpp"

class Game
{

public:
    Physics *physics = nullptr;
    Renderer *renderer = nullptr;
    Mixer *mixer = nullptr;
    Controls *controls = nullptr;
    Resources *resources = nullptr;

    ~Game();

    // Delete copy constructor
    Game(const Game &) = delete;

    static Game *getInstance();
    static void deleteInstance();

    void run();
    void stop();

    // Don't call this function directly. It's exposed for unit test access.
    void __tick(float dt);

    void setFPS(float newFPS) { fps = newFPS; };
    float getFPS() { return actualFPS; };
    void setRootObject(Object *object);

    float getRandomFloat();
    bool shouldHappen(float probability);

    template <typename T, typename... Args>
    static T *create(Args &&...args)
    {
        static_assert(std::is_base_of<Object, T>::value, "T must derive from Object");

        T *obj = new T(std::forward<Args>(args)...);

        obj->__init();

        return obj;
    }

    template <typename T>
    static void destroy(T *obj)
    {
        static_assert(std::is_base_of<Object, T>::value, "T must derive from Object");

        obj->__cleanup();

        delete obj;
    }

private:
    static Game *instancePtr;

    float fps = 30.0f;
    float actualFPS = 30.f;

    std::atomic<bool> running = false;

    Object *rootObject = nullptr;
    Object *oldRootObject = nullptr;

    std::mt19937 randomGenerator;
    std::uniform_real_distribution<float> randomDistribution;

    Game();

    void input();
    void update(float dt);
    void output();
    void checkDeleteObjects();
};