#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <functional>
#include <unordered_map>

#include "jengine/basics/Vector.hpp"
#include "jengine/basics/Events.hpp"

class Controls
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

    Controls();
    ~Controls();

    void input();

    int addKeyHandler(std::function<void(std::string key, bool pressed)> handler);
    void removeKeyHandler(int id);

    int addMouseHandler(std::function<void(MouseEventType eventType, bool pressed, Vector mousePosition)> handler);
    void removeMouseHandler(int id);

    void registerKeys(const std::string &name, const std::string &key);
    const std::string getMapping(const std::string &name);
    bool isMapping(const std::string &name, const std::string &key);
    void clearMappings();

private:
    Events events;

    std::unordered_map<std::string, std::string> keyMappings;
};
