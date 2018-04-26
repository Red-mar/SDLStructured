#include "soundeffects.h"
#include "log.h"

SoundEffects* SoundEffects::instance = nullptr;

SoundEffects* SoundEffects::getInstance()
{
    if (!instance)
    {
        instance = new SoundEffects();
    }
    return instance;
}

SoundEffects::SoundEffects()
{
    load();
}

SoundEffects::~SoundEffects()
{
    for(auto effect : soundEffects)
    {
        Mix_FreeChunk(effect.second);
    }
}

void SoundEffects::play(std::string name)
{
    if (soundEffects[name])
    {
        Mix_PlayChannel(-1, soundEffects[name], 0);
    } else {
        Log::error("Mix_PlayChannel: Could not find sound effect: " + name);
    }

}

void SoundEffects::setVolume(Uint8 setVolume )
{
    for(auto effect : soundEffects)
    {
        effect.second->volume = setVolume;
    }
}

Uint8 SoundEffects::getVolume()
{
    Uint8 volume = 0;
    for(auto effect : soundEffects)
    {
        volume = effect.second->volume;
    }
    return volume;
}

void SoundEffects::load()
{
    soundEffects["test"] = Mix_LoadWAV("assets/wololo.wav");
    soundEffects["jump"] = Mix_LoadWAV("assets/jump.wav");
}