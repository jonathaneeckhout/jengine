#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <unordered_map>

#include "jengine/basics/Object.hpp"
#include "jengine/basics/Vector.hpp"

class Controls : public Object
{
public:
    enum MouseEventType
    {
        MOUSE_LEFT_BUTTON,
        MOUSE_RIGHT_BUTTON,
        MOUSE_MIDDLE_BUTTON,
        MOUSE_MOVEMENT
    };

    std::function<void()> onStop = nullptr;

    ~Controls();

    // Delete copy constructor
    Controls(const Controls &) = delete;

    static Controls *getInstance();
    static void deleteInstance();

    void input() override;

    int addKeyHandler(std::function<void(const std::string &key, bool pressed)> handler);
    void removeKeyHandler(int id);

    int addMouseHandler(std::function<void(MouseEventType eventType, bool pressed, Vector mousePosition)> handler);
    void removeMouseHandler(int id);

    void registerKeys(const std::string &name, const std::string &key);
    const std::string getMapping(const std::string &name);
    bool isMapping(const std::string &name, const std::string &key);
    void clearMappings();

private:
    static Controls *instancePtr;

    int nextKeyHandlerId = 1;
    std::unordered_map<int, std::function<void(std::string, bool)>> keyHandlers;

    int nextMouseHandlerId = 1;
    std::unordered_map<int, std::function<void(MouseEventType, bool, Vector)>> mouseHandlers;

    std::unordered_map<std::string, std::string> keyMappings;

    Controls();

    void invokeKeyHandlers(const std::string &key, bool pressed);
    void invokeMouseHandlers(MouseEventType eventType, bool pressed, Vector mousePosition);
};
