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
    SDL_AudioDeviceID audioDevice;

    Mixer();
    ~Mixer();

    void update(float dt);

    bool loadSound(const std::string &soundName, const std::string &resourceName);
    bool loadSound(const std::string &soundName, const std::string &resourceName, float volume);
    bool unloadSound(const std::string &soundName);

    bool playSound(const std::string &soundName);
    bool stopSound(const std::string &soundName);
    void stopAllSounds();

    void setMasterVolume(int volume);
    void mute();
    void unMute();

    bool isMuted();

    void __onChannelFinished(int channel);

private:
    std::unordered_map<std::string, Mix_Chunk *> sounds;
    std::unordered_map<std::string, std::unordered_set<int>> playingChannels;
    std::unordered_map<int, std::string> channelToSound;

    std::vector<int> channelsToRemove;
    std::mutex channelsMutex;

    int masterVolume = MIX_MAX_VOLUME;
    bool muted = false;

    static void channelFinishedCallback(int channel);
    void processDeferredRemovals();
    void removeChannel(int channel);
};