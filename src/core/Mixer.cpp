#include "jengine/core/Mixer.hpp"
#include "jengine/core/Game.hpp"
#include "jengine/core/Resources.hpp"

Mixer::Mixer()
{
    if (!MIX_Init())
    {
        throw std::runtime_error("Couldn't initialize SDL_mixer");
    }

    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (!mixer)
    {
        MIX_Quit();

        throw std::runtime_error("Failed to open audiodevice");
    }
}

Mixer::~Mixer() noexcept
{
    for (auto &[name, track] : sounds)
    {
        MIX_DestroyTrack(track);
    }

    sounds.clear();

    MIX_DestroyMixer(mixer);

    MIX_Quit();
}

bool Mixer::loadSound(const std::string &soundName, const std::string &resourceName)
{
    if (getSound(soundName) != nullptr)
    {
        return false;
    }

    auto resource = Game::getInstance()->resources->createResourceStream(resourceName);
    if (resource == nullptr)
    {
        return false;
    }

    MIX_Audio *audio = MIX_LoadAudio_IO(mixer, resource, false, true);
    if (audio == nullptr)
    {
        return false;
    }

    MIX_Track *track = MIX_CreateTrack(mixer);
    if (track == nullptr)
    {
        MIX_DestroyAudio(audio);
        return false;
    }

    if (!MIX_SetTrackAudio(track, audio))
    {
        MIX_DestroyTrack(track);

        MIX_DestroyAudio(audio);
        return false;
    }

    MIX_DestroyAudio(audio);

    sounds[soundName] = track;

    return true;
}

bool Mixer::loadSound(const std::string &soundName, const std::string &resourceName, float volume)
{

    if (!loadSound(soundName, resourceName))
    {
        return false;
    }

    MIX_Track *track = getSound(soundName);

    return MIX_SetTrackGain(track, volume);
}

bool Mixer::unloadSound(const std::string &soundName)
{

    auto it = sounds.find(soundName);
    if (it == sounds.end())
    {
        return false;
    }

    MIX_DestroyTrack(it->second);

    sounds.erase(it);

    return true;
}

bool Mixer::playSound(const std::string &soundName)
{
    auto sound = getSound(soundName);
    if (sound == nullptr)
    {
        return false;
    }

    return MIX_PlayTrack(sound, 0);
}

bool Mixer::stopSound(const std::string &soundName)
{
    auto sound = getSound(soundName);
    if (sound == nullptr)
    {
        return false;
    }

    return MIX_StopTrack(sound, 0);
}

void Mixer::setMasterVolume(int volume)
{
    MIX_SetMixerGain(mixer, volume);
}

void Mixer::mute()
{
    muted = true;

    last_volume = MIX_GetMixerGain(mixer);

    setMasterVolume(0);
}

void Mixer::unMute()
{
    muted = false;

    setMasterVolume(last_volume);
}

bool Mixer::isMuted() const
{
    return muted;
}

MIX_Track *Mixer::getSound(const std::string &soundName) const
{
    auto sound = sounds.find(soundName);
    if (sound == sounds.end())
    {
        return nullptr;
    }

    return sound->second;
}