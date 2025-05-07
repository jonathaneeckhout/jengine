#pragma once

#include <string>
#include <map>
#include <SDL2/SDL_ttf.h>

#include "jengine/Object.hpp"

class Resources : public Object
{
public:
    std::map<std::string, SDL_RWops *> fonts;

    ~Resources();

    Resources(const Resources &) = delete;

    static Resources *getInstance();
    static void deleteInstance();

    bool loadFont(const std::string &name, unsigned char *font, unsigned int size);

private:
    static Resources *instancePtr;

    Resources();

    void cleanFonts();
};