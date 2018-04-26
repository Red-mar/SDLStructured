#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include "sdl.hpp"
#include <unordered_map>

class SoundEffects
{
  public:
    static SoundEffects *getInstance(); // NOTE
    SoundEffects();
    ~SoundEffects();

    SoundEffects(SoundEffects const &){};
    void operator=(SoundEffects const &){};

    void play(std::string name);
    void setVolume(Uint8 volume);
    Uint8 getVolume();

  private:
    static SoundEffects* instance;
    std::unordered_map<std::string, Mix_Chunk *> soundEffects;

    int channel;

    void load();
};

#endif // !SOUNDEFFECT_H
