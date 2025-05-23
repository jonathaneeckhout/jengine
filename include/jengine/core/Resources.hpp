#pragma once

#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>

#include "jengine/basics/Object.hpp"

class Resources : public Object
{
public:
    ~Resources();

    Resources(const Resources &) = delete;

    static Resources *getInstance();
    static void deleteInstance();

    bool loadResource(const std::string &name, unsigned char *data, size_t size);

    SDL_IOStream *getResource(const std::string &name);

private:
    static Resources *instancePtr;

    std::unordered_map<std::string, SDL_IOStream *> resources;

    Resources();
};