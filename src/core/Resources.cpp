#include "jengine/core/Resources.hpp"

Resources *Resources::instancePtr = nullptr;

Resources::Resources() : Object()
{
    setName("Resources");
}

Resources::~Resources() {}

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

bool Resources::loadFont(const std::string &name, unsigned char *font, unsigned int size)
{
    fonts[name] = std::vector<unsigned char>(font, font + size);
    return true;
}
