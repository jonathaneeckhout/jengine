#include <iostream>

#include "jengine/core/Mixer.hpp"
#include "jengine/core/Resources.hpp"

Mixer *Mixer::instancePtr = nullptr;

Mixer::Mixer() : Object()
{
    setName("Mixer");

    audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!audioDevice)
    {
        throw std::runtime_error("Failed to open audiodevice");
    }

    if (!Mix_OpenAudio(audioDevice, NULL))
    {
        throw std::runtime_error("Failed to open  mixer");
    }
}

Mixer::~Mixer()
{
    Mix_CloseAudio();

    SDL_CloseAudioDevice(audioDevice);
}

Mixer *Mixer::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new Mixer();
    }
    return instancePtr;
}

void Mixer::deleteInstance()
{
    if (instancePtr != nullptr)
    {
        delete instancePtr;
        instancePtr = nullptr;
    }
}

bool Mixer::loadSound(const std::string &soundName, const std::string &resourceName)
{
    auto resource = Resources::getInstance()->getResource(resourceName);
    if (resource == nullptr)
    {
        return false;
    }

    auto sound = Mix_LoadWAV_IO(resource, 0);
    if (sound == NULL)
    {
        return false;
    }

    sounds[soundName] = sound;

    return true;
}

bool Mixer::loadSound(const std::string &soundName, const std::string &resourceName, float volume)
{
    auto resource = Resources::getInstance()->getResource(resourceName);
    if (resource == nullptr)
    {
        return false;
    }

    auto sound = Mix_LoadWAV_IO(resource, 0);
    if (sound == NULL)
    {
        return false;
    }

    Mix_VolumeChunk(sound, static_cast<int>(MIX_MAX_VOLUME * volume));

    sounds[soundName] = sound;

    return true;
}

bool Mixer::playSound(const std::string &soundName)
{
    auto sound = sounds.find(soundName);
    if (sound == sounds.end())
    {
        return false;
    }

    if (Mix_PlayChannel(-1, sound->second, 0) == -1)
    {
        return false;
    }

    return true;
}

void Mixer::setMasterVolume(int volume)
{
    masterVolume = volume;

    Mix_MasterVolume(masterVolume);
}

void Mixer::mute()
{
    muted = true;

    Mix_MasterVolume(0);
}

void Mixer::unMute()
{
    muted = false;

    Mix_MasterVolume(masterVolume);
}

bool Mixer::isMuted()
{
    return muted;
}