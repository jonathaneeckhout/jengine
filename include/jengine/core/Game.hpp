#pragma once
#include <atomic>
#include <string>
#include <memory>

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

    void setFPS(float newFPS);
    void setRootObject(std::shared_ptr<Object> object);

    template <typename T, typename... Args>
    static std::shared_ptr<T> create(Args &&...args)
    {
        static_assert(std::is_base_of<Object, T>::value, "T must derive from Object");

        std::shared_ptr<T> obj = std::make_shared<T>(std::forward<Args>(args)...);

        obj->__init();

        return obj;
    }

    template <typename T>
    static void destroy(std::shared_ptr<T> obj)
    {
        static_assert(std::is_base_of<Object, T>::value, "T must derive from Object");

        obj->__cleanup();
    }

    template <typename T>
    static std::shared_ptr<T> safeCast(const std::weak_ptr<Object> &weak)
    {
        auto sp = weak.lock();
        return std::dynamic_pointer_cast<T>(sp);
    }

private:
    static Game *instancePtr;

    float fps = 30.0f;

    std::atomic<bool> running;

    Physics *phyics = nullptr;
    Renderer *renderer = nullptr;
    Controls *controls = nullptr;
    Resources *resources = nullptr;

    std::shared_ptr<Object> rootObject = nullptr;

    Game();

    void input();
    void update(float dt);
    void output();
    void checkDeleteObjects();
};