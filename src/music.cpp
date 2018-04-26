#include "music.h"
#include "log.h"

Music::Music(std::string file) : music(nullptr),
                                 filepath(file)
{
    music = Mix_LoadMUS(file.c_str());
    if (!music)
    {
        Log::log("Mix_LoadMUS: could not load " + filepath + ", error: " + Mix_GetError());
    } else {
        Log::debug("Music loaded from " + filepath);
    }
}

Music::~Music()
{
    if (music)
    {
        Mix_FreeMusic(music);
    }
}

bool Music::play(int times, int fadeInMs)
{
    if (!music)
    {
        return false;
    }

    if (Mix_FadeInMusic(music, times, fadeInMs))
    {
        Log::error("Mix_FadeInMusic: Could not play " + filepath);
        return false;
    }

    Log::debug("Playing musisc...");
    return true;
}

void Music::fadeOut(int ms)
{
    Mix_FadeOutMusic(ms);
}

void Music::stop()
{
    Mix_HaltMusic();
    Log::debug("Stopping music...");
}

void Music::pause()
{
    Mix_PauseMusic();
    Log::debug("Pausing music...");
}

void Music::unpause()
{
    Mix_ResumeMusic();
    Log::debug("Unpausing music...");
}

void Music::restart()
{
    stop();
    play();
}

void Music::rewind()
{
    Mix_RewindMusic();
}

void Music::setPosition(double seconds)
{
    rewind();
    if (Mix_SetMusicPosition(seconds) == -1)
    {
        Log::error("Mix_SetMusicPosition: could not set music position, error: " + std::string(Mix_GetError()));
    }
}

bool Music::isPlaying()
{
    return (Mix_PlayingMusic() && !isPaused());
}

bool Music::isPaused()
{
    return (bool)Mix_PausedMusic();
}

bool Music::isFadingIn()
{
	return (Mix_FadingMusic() == MIX_FADING_IN);
}
bool Music::isFadingOut()
{
	return (Mix_FadingMusic() == MIX_FADING_OUT);
}
int Music::setVolume(int volume)
{
	if (volume > MIX_MAX_VOLUME)
		Log::warning("Mix_VolumeMusic: Tried to overflow volume");

	return Mix_VolumeMusic(volume);
}
int Music::getVolume()
{
	return Mix_VolumeMusic(-1);
}
int Music::getMaxVolume()
{
	return MIX_MAX_VOLUME;
}

