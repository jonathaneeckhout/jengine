#include "jengine/core/Controls.hpp"

Controls *Controls::instancePtr = NULL;

Controls::Controls() : Object()
{
    name = "Controls";
}

Controls::~Controls() {}

Controls *Controls::getInstance()
{
    if (instancePtr == NULL)
    {
        instancePtr = new Controls();
    }
    return instancePtr;
}

void Controls::deleteInstance()
{
    if (instancePtr != NULL)
    {
        delete instancePtr;
        instancePtr = NULL;
    }
}

void Controls::input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            if (onStop != NULL)
            {
                onStop();
            }
            break;
        case SDL_KEYDOWN:
        {
            SDL_Keycode keycode = event.key.keysym.sym;

            std::string keyName = SDL_GetKeyName(keycode);

            invokeKeyHandlers(keyPressHandlers, keyName);
        }
        break;
        case SDL_KEYUP:
        {
            SDL_Keycode keycode = event.key.keysym.sym;

            std::string keyName = SDL_GetKeyName(keycode);

            invokeKeyHandlers(keyReleaseHandlers, keyName);
        }
        break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                invokeMouseHandlers(mouseLeftClickHandlers, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_RIGHT:
                invokeMouseHandlers(mouseRightClickHandlers, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_MIDDLE:
                invokeMouseHandlers(mouseMiddleClickHandlers, Vector{float(event.button.x), float(event.button.y)});
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                invokeMouseHandlers(mouseLeftReleaseHandlers, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_RIGHT:
                invokeMouseHandlers(mouseRightReleaseHandlers, Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_MIDDLE:
                invokeMouseHandlers(mouseMiddleReleaseHandlers, Vector{float(event.button.x), float(event.button.y)});
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            invokeMouseHandlers(mouseMovementHandlers, Vector{float(event.motion.x), float(event.motion.y)});
            break;
        default:
            break;
        }
    }
}

void Controls::invokeKeyHandlers(const std::vector<std::function<void(std::string)>> &handlers, const std::string &key)
{
    for (const auto &handler : handlers)
    {
        handler(key);
    }
}

void Controls::invokeMouseHandlers(const std::vector<std::function<void(Vector)>> &handlers, const Vector &mousePosition)
{
    for (const auto &handler : handlers)
    {
        handler(mousePosition);
    }
}