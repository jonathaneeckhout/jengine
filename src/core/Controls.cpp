#include "jengine/core/Controls.hpp"

Controls *Controls::instancePtr = nullptr;

Controls::Controls() : Object()
{
    setName("Controls");
}

Controls::~Controls() {}

Controls *Controls::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new Controls();
    }
    return instancePtr;
}

void Controls::deleteInstance()
{
    if (instancePtr != nullptr)
    {
        delete instancePtr;
        instancePtr = nullptr;
    }
}

void Controls::input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            if (onStop != nullptr)
            {
                onStop();
            }
            break;
        case SDL_EVENT_KEY_DOWN:
        {
            SDL_Keycode keycode = event.key.key;

            std::string keyName = SDL_GetKeyName(keycode);

            invokeKeyHandlers(keyName, true);
        }
        break;
        case SDL_EVENT_KEY_UP:
        {
            SDL_Keycode keycode = event.key.key;

            std::string keyName = SDL_GetKeyName(keycode);

            invokeKeyHandlers(keyName, false);
        }
        break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                invokeMouseHandlers(MOUSE_LEFT_BUTTON, true, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_RIGHT:
                invokeMouseHandlers(MOUSE_RIGHT_BUTTON, true, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_MIDDLE:
                invokeMouseHandlers(MOUSE_MIDDLE_BUTTON, true, Vector{float(event.button.x), float(event.button.y)});
                break;
            default:
                break;
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                invokeMouseHandlers(MOUSE_LEFT_BUTTON, false, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_RIGHT:
                invokeMouseHandlers(MOUSE_RIGHT_BUTTON, false, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_MIDDLE:
                invokeMouseHandlers(MOUSE_MIDDLE_BUTTON, false, Vector{float(event.button.x), float(event.button.y)});
                break;
            default:
                break;
            }
            break;
        case SDL_EVENT_MOUSE_MOTION:
            invokeMouseHandlers(MOUSE_MOVEMENT, false, Vector{float(event.motion.x), float(event.motion.y)});
            break;
        default:
            break;
        }
    }
}

int Controls::addKeyHandler(std::function<void(const std::string &key, bool pressed)> handler)
{
    int id = nextKeyHandlerId++;
    keyHandlers[id] = std::move(handler);
    return id;
}

void Controls::removeKeyHandler(int id)
{
    keyHandlers.erase(id);
}

int Controls::addMouseHandler(std::function<void(MouseEventType eventType, bool pressed, Vector coordinates)> handler)
{
    int id = nextMouseHandlerId++;
    mouseHandlers[id] = std::move(handler);
    return id;
}

void Controls::removeMouseHandler(int id)
{
    mouseHandlers.erase(id);
}

void Controls::invokeKeyHandlers(const std::string &key, bool pressed)
{
    for (const auto &[id, handler] : keyHandlers)
    {
        handler(key, pressed);
    }
}

void Controls::invokeMouseHandlers(MouseEventType eventType, bool pressed, Vector mousePosition)
{
    for (const auto &[id, handler] : mouseHandlers)
    {
        handler(eventType, pressed, mousePosition);
    }
}

void Controls::registerKeys(const std::string &name, const std::string &key)
{
    keyMappings[name] = key;
}

const std::string Controls::getMapping(const std::string &name)
{
    auto mapping = keyMappings.find(name);
    if (mapping == keyMappings.end())
    {
        return "";
    }

    return mapping->second;
}

bool Controls::isMapping(const std::string &name, const std::string &key)
{
    auto mapping = getMapping(name);
    if (mapping == "")
    {
        return false;
    }

    return key == mapping;
}

void Controls::clearMappings()
{
    keyMappings.clear();
}
