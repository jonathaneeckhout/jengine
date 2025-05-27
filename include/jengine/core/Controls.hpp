#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <unordered_map>

#include "jengine/basics/Object.hpp"
#include "jengine/basics/Vector.hpp"

class Controls : public Object
{
public:
    std::function<void()> onStop = nullptr;

    std::vector<std::function<void(std::string)>> keyPressHandlers = {};
    std::vector<std::function<void(std::string)>> keyReleaseHandlers = {};

    std::vector<std::function<void(Vector)>> mouseLeftClickHandlers = {};
    std::vector<std::function<void(Vector)>> mouseLeftReleaseHandlers = {};

    std::vector<std::function<void(Vector)>> mouseRightClickHandlers = {};
    std::vector<std::function<void(Vector)>> mouseRightReleaseHandlers = {};

    std::vector<std::function<void(Vector)>> mouseMiddleClickHandlers = {};
    std::vector<std::function<void(Vector)>> mouseMiddleReleaseHandlers = {};

    std::vector<std::function<void(Vector)>> mouseMovementHandlers = {};

    ~Controls();

    // Delete copy constructor
    Controls(const Controls &) = delete;

    static Controls *getInstance();
    static void deleteInstance();

    void input() override;

    void registerKeys(const std::string &name, const std::string &key);
    const std::string getMapping(const std::string &name);
    bool isMapping(const std::string &name, const std::string &key);
    void clearMappings();

private:
    static Controls *instancePtr;

    std::unordered_map<std::string, std::string> keyMappings;

    Controls();

    static void invokeKeyHandlers(const std::vector<std::function<void(std::string)>> &handlers, const std::string &key);
    static void invokeMouseHandlers(const std::vector<std::function<void(Vector)>> &handlers, const Vector &mousePosition);
};
