#include "Semaphore.hpp"

Semaphore::Semaphore()
    : mSemaphore( SDL_CreateSemaphore( 1 ) ), mCoherentThreads( 1 )
{
}

Semaphore::Semaphore( int coherentThreads )
    : mSemaphore( SDL_CreateSemaphore( coherentThreads ) ), mCoherentThreads( coherentThreads )
{
}

Semaphore::~Semaphore()
{
    SDL_DestroySemaphore( mSemaphore );
    mSemaphore = NULL;
}

void
Semaphore::lock()
{
    SDL_SemWait( mSemaphore );
}

void
Semaphore::unlock()
{
    SDL_SemPost( mSemaphore );
}

