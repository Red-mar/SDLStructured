#ifndef MUSIC_H
#define MUSIC_H

#include "sdl.hpp"

class Music
{
    public:
        Music(std::string file);

        virtual ~Music();

        bool play(int times=-1, int fadeInMs=0);
        void fadeOut(int ms);
        void stop();
        void pause();
        void unpause();
        void restart();
        void rewind();
        void setPosition(double seconds);
        bool isPlaying();
        bool isPaused();
        bool isFadingIn();
        bool isFadingOut();
        int setVolume(int volume);
        int getVolume();
        int getMaxVolume();
    private:
        Mix_Music* music;
        std::string filepath;
};

#endif // !MUSIC_H
