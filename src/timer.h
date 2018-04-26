#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <sstream>
#include "stdint.h"

class Timer
{
    public:
        Timer();

        void start();
        void stop();
        void pause();
        void restart();
        void unpause();
        bool isRunning();
        bool isPaused();
        
        unsigned int getTicks();
    private:
        unsigned int mStartTicks;
        unsigned int mPausedTicks;

        bool mPaused;
        bool mStarted;
};

#endif // !TIMER_H
