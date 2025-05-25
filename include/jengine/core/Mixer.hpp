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

    bool loadSound(const std::string &soundName, const std::string &soundFile);
    bool playSound(const std::string &soundName);

private:
    static Mixer *instancePtr;

    std::unordered_map<std::string, Mix_Chunk *> sounds;

    Mixer();
};