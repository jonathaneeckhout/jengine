#include <iostream>

#include "jengine/core/Mixer.hpp"

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

bool Mixer::loadSound(const std::string &soundName, const std::string &soundFile)
{
    auto sound = Mix_LoadWAV(soundFile.c_str());
    if (sound == NULL)
    {
        return false;
    }

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
