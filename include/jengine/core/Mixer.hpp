#pragma once

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <mutex>

class Mixer
{
public:
    MIX_Mixer *mixer;

    Mixer();
    ~Mixer() noexcept;

    bool loadSound(const std::string &soundName, const std::string &resourceName);
    bool loadSound(const std::string &soundName, const std::string &resourceName, float volume);
    bool unloadSound(const std::string &soundName);

    bool playSound(const std::string &soundName);
    bool stopSound(const std::string &soundName);

    void setMasterVolume(int volume);
    void mute();
    void unMute();

    bool isMuted() const;

private:
    std::unordered_map<std::string, MIX_Track *> sounds;

    bool muted = false;

    float last_volume = 100.0f;

    MIX_Track *getSound(const std::string &soundName) const;
};