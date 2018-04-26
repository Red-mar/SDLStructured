#include "sdl.hpp"
#include "Log.h"

bool SDL::init()
{
    int flags;

    if (SDL_Init(0) < 0)
    {
        Log::error("SDL_Init: could not start SDL");
        Log::error(std::string(SDL_GetError()));
        throw "SDL Init failed";
    }
    Log::verbose("Started SDL.");

    if (SDL_WasInit(SDL_INIT_AUDIO) != 0)
    {
        Log::error("SDL_WasInit: Could not reinitialize audio, error: ");
        Log::error(SDL_GetError());
        throw "SDL_WasInit Fail";
    }

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        Log::error("SDL_InitSubsystem: Could not reinitialize audio, error: ");
        Log::error(SDL_GetError());
        throw "SDL_INIT Fail";
    }

    /* what does this do
    flags = MIX_INIT_MP3;

    if ((Mix_Init(flags) & flags) != flags)
    {
        Log::error("Mix_Init: could not start audio");
        Log::error(Mix_GetError());
    }
*/
    if (-1 == Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048))
    {
        Log::error("Mix_OpenAudio: could not start audio");
        Log::error(Mix_GetError());
    }
    Log::verbose("Initialized audio.");

    Mix_AllocateChannels(16);

    flags = (SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);

    if (SDL_WasInit(flags) != 0)
    {
        Log::error("SDL_WasInit: tried to initialize video");
        Log::error(std::string(SDL_GetError()));
        throw "SDL_WasInit Failed";
    }
    if (SDL_InitSubSystem(flags) < 0)
    {
        Log::error("SDL_InitSubsystem: tried to initialize video");
        Log::error(std::string(SDL_GetError()));
        throw "SDL_InitSubSystem Failed";
    }
    Log::verbose("Initialized video.");

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        Log::error("IMG_INIT: could not initialize png support");
        Log::error(std::string(SDL_GetError()));
        throw "IMG_INIT Failed";
    }
    Log::verbose("Initialized image support.");
    if (TTF_Init() == -1)
    {
        Log::error("TTF_Init: Couldn't start TTF support");
        Log::error(TTF_GetError());
        throw "TTF_Init Failed";
    }
    Log::verbose("Initialization complete.");
    return true;
}

void SDL::exit()
{
    Mix_AllocateChannels(0);
    Mix_Quit();
    Mix_CloseAudio();
    if (TTF_WasInit())
    {
        TTF_Quit();
    }

    SDL_Quit();
}