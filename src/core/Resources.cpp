#include "jengine/core/Resources.hpp"

Resources::Resources() {}

Resources::~Resources() {}

bool Resources::loadResource(const std::string &name, const unsigned char *data, size_t size)
{
    if (data == nullptr || size == 0)
    {
        return false;
    }

    ResourceData res;
    res.data = data;
    res.size = size;
    resources[name] = std::move(res);
    return true;
}

SDL_IOStream *Resources::getResource(const std::string &name) const
{
    auto it = resources.find(name);
    if (it == resources.end())
    {
        return nullptr;
    }

    return SDL_IOFromConstMem(it->second.data, it->second.size);
}
