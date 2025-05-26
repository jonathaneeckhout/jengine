#pragma once

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <unordered_map>

#include "jengine/basics/Object.hpp"    

class Mixer : public Object
{
public:
    SDL_AudioDeviceID audioDevice;

    ~Mixer();

    Mixer(const Mixer &) = delete;

    static Mixer *getInstance();
    static void deleteInstance();

    bool loadSound(const std::string &soundName, const std::string &resourceName);
    bool loadSound(const std::string &soundName, const std::string &resourceName, float volume);

    bool playSound(const std::string &soundName);

    void setMasterVolume(int volume);
    void mute();
    void unMute();

    bool isMuted();

private:
    static Mixer *instancePtr;

    std::unordered_map<std::string, Mix_Chunk *> sounds;

    int masterVolume = MIX_MAX_VOLUME;
    bool muted = false;

    Mixer();
};