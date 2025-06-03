#include <iostream>

#include "jengine/core/Mixer.hpp"
#include "jengine/core/Game.hpp"
#include "jengine/core/Resources.hpp"

Mixer::Mixer()
{
    audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!audioDevice)
    {
        throw std::runtime_error("Failed to open audiodevice");
    }

    if (!Mix_OpenAudio(audioDevice, NULL))
    {
        throw std::runtime_error("Failed to open  mixer");
    }

    Mix_ChannelFinished(&Mixer::channelFinishedCallback);
}

Mixer::~Mixer()
{
    for (auto sound : sounds)
    {
        Mix_FreeChunk(sound.second);
    }

    stopAllSounds();

    Mix_Volume(-1, 0);

    Mix_CloseAudio();

    SDL_CloseAudioDevice(audioDevice);
}

void Mixer::update(float)
{
    processDeferredRemovals();
}

bool Mixer::loadSound(const std::string &soundName, const std::string &resourceName)
{
    auto resource = Game::getInstance()->resources->getResource(resourceName);
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
    auto resource = Game::getInstance()->resources->getResource(resourceName);
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

    int channel = Mix_PlayChannel(-1, sound->second, 0);
    if (channel == -1)
    {
        return false;
    }

    playingChannels[soundName].insert(channel);
    channelToSound[channel] = soundName;

    return true;
}

bool Mixer::stopSound(const std::string &soundName)
{
    auto it = playingChannels.find(soundName);
    if (it == playingChannels.end())
    {
        return false;
    }

    for (int channel : it->second)
    {
        Mix_HaltChannel(channel);
        channelToSound.erase(channel);
    }

    playingChannels.erase(it);
    return true;
}

void Mixer::stopAllSounds()
{
    Mix_HaltChannel(-1);

    playingChannels.clear();

    channelToSound.clear();
}

void Mixer::channelFinishedCallback(int channel)
{
    Game::getInstance()->mixer->__onChannelFinished(channel);
}

void Mixer::__onChannelFinished(int channel)
{
    std::lock_guard<std::mutex> lock(channelsMutex);
    channelsToRemove.push_back(channel);
}

void Mixer::processDeferredRemovals()
{
    std::lock_guard<std::mutex> lock(channelsMutex);
    for (int channel : channelsToRemove)
    {
        removeChannel(channel);
    }
    channelsToRemove.clear();
}

void Mixer::removeChannel(int channel)
{
    auto it = channelToSound.find(channel);
    if (it != channelToSound.end())
    {
        const std::string &soundName = it->second;
        auto pit = playingChannels.find(soundName);
        if (pit != playingChannels.end())
        {
            pit->second.erase(channel);
            if (pit->second.empty())
            {
                playingChannels.erase(pit);
            }
        }
        channelToSound.erase(it);
    }
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