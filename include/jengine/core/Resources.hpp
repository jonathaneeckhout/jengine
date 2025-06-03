#pragma once

#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>

class Resources
{
public:
    Resources();
    ~Resources();

    bool loadResource(const std::string &name, unsigned char *data, size_t size);

    SDL_IOStream *getResource(const std::string &name);

private:
    std::unordered_map<std::string, SDL_IOStream *> resources;
};