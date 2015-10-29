#ifndef _CONDITION_HPP_
#define _CONDITION_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "Mutex.hpp"

class Mutex; // TODO blöd

class Condition
{
    private:
        SDL_cond* mCondition;
        Mutex* mMutex;

    public:
        Condition();
        Condition( Mutex* mutex );
        ~Condition();

        void wait();
        void signal();

        void attachMutex( Mutex* mutex );
};

#endif

