#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <SDL2/SDL.h>

class LTimer
{
    private:
        Uint32 mStartTicks;
        Uint32 mPausedTicks;

        bool mPaused;
        bool mStarted;

    public:
        LTimer();
        ~LTimer();

        void start();
        void stop();
        void pause();
        void resume();

        Uint32 getTicks();

        bool isStarted();
        bool isPaused();
};

#endif

