#pragma once

#include <unordered_set>
#include <string>

#include "jengine/basics/Object.hpp"

class SoundLoaderComponent : public Object
{
public:
    SoundLoaderComponent();
    ~SoundLoaderComponent();

    bool addSound(const std::string &soundName, const std::string &resourceName);
    bool addSound(const std::string &soundName, const std::string &resourceName, float volume);
    bool removeSound(const std::string &soundName);

private:
    std::unordered_set<std::string> loadedSounds;
};