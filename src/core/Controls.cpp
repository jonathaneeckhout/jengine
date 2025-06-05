#include "jengine/core/Controls.hpp"

Controls::Controls()
{
    events.createEvent<std::string, bool>("onKey");
    events.createEvent<MouseEventType, bool, Vector>("onMouse");
}

Controls::~Controls() {}

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

            events.trigger("onKey", keyName, true);
        }
        break;
        case SDL_EVENT_KEY_UP:
        {
            SDL_Keycode keycode = event.key.key;

            std::string keyName = SDL_GetKeyName(keycode);

            events.trigger("onKey", keyName, false);
        }
        break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                events.trigger("onMouse", MOUSE_LEFT_BUTTON, true, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_RIGHT:
                events.trigger("onMouse", MOUSE_RIGHT_BUTTON, true, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_MIDDLE:
                events.trigger("onMouse", MOUSE_MIDDLE_BUTTON, true, Vector{float(event.button.x), float(event.button.y)});
                break;
            default:
                break;
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                events.trigger("onMouse", MOUSE_LEFT_BUTTON, false, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_RIGHT:
                events.trigger("onMouse", MOUSE_RIGHT_BUTTON, false, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_MIDDLE:
                events.trigger("onMouse", MOUSE_MIDDLE_BUTTON, false, Vector{float(event.button.x), float(event.button.y)});
                break;
            default:
                break;
            }
            break;
        case SDL_EVENT_MOUSE_MOTION:
            events.trigger("onMouse", MOUSE_MOVEMENT, false, Vector{float(event.motion.x), float(event.motion.y)});
            break;
        default:
            break;
        }
    }

    events.processAll();
}

int Controls::addKeyHandler(std::function<void(std::string key, bool pressed)> handler)
{
    return events.addHandler<std::string, bool>("onKey", handler);
}

void Controls::removeKeyHandler(int id)
{
    events.removeHandler("onKey", id);
}

int Controls::addMouseHandler(std::function<void(MouseEventType eventType, bool pressed, Vector coordinates)> handler)
{
    return events.addHandler<MouseEventType, bool, Vector>("onMouse", handler);
}

void Controls::removeMouseHandler(int id)
{
    events.removeHandler("onMouse", id);
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
