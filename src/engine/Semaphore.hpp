#ifndef _SEMAPHORE_HPP_
#define _SEMAPHORE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

class Semaphore
{
    private:
        SDL_sem* mSemaphore;
        int mCoherentThreads;

    public:
        Semaphore();
        Semaphore( int coherentThreads );
        ~Semaphore();

        void lock();
        void unlock();
};

#endif

