#pragma once

#include <string>
#include <unordered_map>
#include <SDL3_ttf/SDL_ttf.h>

#include "jengine/basics/Object.hpp"

class Resources : public Object
{
public:
    std::unordered_map<std::string, std::vector<unsigned char>> fonts;

    ~Resources();

    Resources(const Resources &) = delete;

    static Resources *getInstance();
    static void deleteInstance();

    bool loadFont(const std::string &name, unsigned char *font, unsigned int size);

private:
    static Resources *instancePtr;

    Resources();
};