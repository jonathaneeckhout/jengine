#include "jengine/core/Resources.hpp"

Resources *Resources::instancePtr = nullptr;

Resources::Resources() : Object()
{
    name = "Resources";
}

Resources::~Resources()
{
    cleanFonts();
}

Resources *Resources::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new Resources();
    }
    return instancePtr;
}

void Resources::deleteInstance()
{
    if (instancePtr != nullptr)
    {
        delete instancePtr;
        instancePtr = nullptr;
    }
}

void Resources::cleanFonts()
{
    for (auto &font : fonts)
    {
        SDL_RWclose(font.second);
    }
}

bool Resources::loadFont(const std::string &name, unsigned char *font, unsigned int size)
{
    SDL_RWops *newFont = SDL_RWFromConstMem(font, size);
    if (newFont == nullptr)
    {
        return false;
    }

    fonts[name] = newFont;

    return true;
}
