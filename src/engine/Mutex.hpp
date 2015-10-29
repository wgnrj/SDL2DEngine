#ifndef _MUTEX_HPP_
#define _MUTEX_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "Condition.hpp"

class Condition; // TODO blöd

class Mutex
{
    private:
        SDL_mutex* mMutex;

    public:
        Mutex();
        ~Mutex();

        void lock();
        void unlock();

        Condition createCondition();

        SDL_mutex* getMutex();
};

#endif

