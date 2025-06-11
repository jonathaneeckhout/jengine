#include "jengine/components/SoundLoaderComponent.hpp"
#include "jengine/core/Game.hpp"
#include "jengine/core/Mixer.hpp"

SoundLoaderComponent::SoundLoaderComponent() {}

SoundLoaderComponent::~SoundLoaderComponent()
{
    auto mixer = Game::getInstance()->mixer;

    for (const auto &soundName : loadedSounds)
    {
        mixer->stopSound(soundName);

        mixer->unloadSound(soundName);
    }

    loadedSounds.clear();
}

bool SoundLoaderComponent::addSound(const std::string &soundName, const std::string &resourceName)
{
    if (loadedSounds.find(soundName) != loadedSounds.end())
    {
        return false;
    }

    auto mixer = Game::getInstance()->mixer;

    if (mixer->loadSound(soundName, resourceName))
    {
        loadedSounds.insert(soundName);
        return true;
    }

    return false;
}

bool SoundLoaderComponent::addSound(const std::string &soundName, const std::string &resourceName, float volume)
{
    if (loadedSounds.find(soundName) != loadedSounds.end())
    {
        return false;
    }

    auto mixer = Game::getInstance()->mixer;

    if (mixer->loadSound(soundName, resourceName, volume))
    {
        loadedSounds.insert(soundName);
        return true;
    }

    return false;
}

bool SoundLoaderComponent::removeSound(const std::string &soundName)
{
    auto it = loadedSounds.find(soundName);
    if (it == loadedSounds.end())
    {
        return false;
    }

    auto mixer = Game::getInstance()->mixer;

    mixer->stopSound(soundName);

    if (mixer->unloadSound(soundName))
    {
        loadedSounds.erase(it);
        return true;
    }

    return false;
}
