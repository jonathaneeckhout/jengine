#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <SDL3/SDL.h>

class Resources
{
public:
    Resources();
    ~Resources();

    bool loadResource(const std::string &name, const unsigned char *data, size_t size);

    SDL_IOStream *getResource(const std::string &name) const;

private:
    struct ResourceData
    {
        const unsigned char *data;
        size_t size;
    };

    std::unordered_map<std::string, ResourceData> resources;
};
