#include "jengine/core/Resources.hpp"

Resources *Resources::instancePtr = NULL;

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
    if (instancePtr == NULL)
    {
        instancePtr = new Resources();
    }
    return instancePtr;
}

void Resources::deleteInstance()
{
    if (instancePtr != NULL)
    {
        delete instancePtr;
        instancePtr = NULL;
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
    if (newFont == NULL)
    {
        return false;
    }

    fonts[name] = newFont;

    return true;
}
