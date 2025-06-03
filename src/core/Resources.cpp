#include "jengine/core/Resources.hpp"

Resources::Resources() {}

Resources::~Resources()
{
    for (auto &resource : resources)
    {
        SDL_CloseIO(resource.second);
    }
}

bool Resources::loadResource(const std::string &name, unsigned char *data, size_t size)
{
    SDL_IOStream *io = SDL_IOFromConstMem(data, size);
    if (io == NULL)
    {
        return false;
    }

    resources[name] = io;

    return true;
}

SDL_IOStream *Resources::getResource(const std::string &name)
{
    auto it = resources.find(name);

    if (it != resources.end())
    {
        return it->second;
    }

    return nullptr;
}
