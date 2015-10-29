#include "Mutex.hpp"

Mutex::Mutex()
    : mMutex( SDL_CreateMutex() )
{
}

Mutex::~Mutex()
{
    SDL_DestroyMutex( mMutex );
    mMutex = NULL;
}

SDL_mutex*
Mutex::getMutex()
{
    return mMutex;
}

void
Mutex::lock()
{
    SDL_LockMutex( mMutex );
}

void
Mutex::unlock()
{
    SDL_UnlockMutex( mMutex );
}

Condition
Mutex::createCondition()
{
    return Condition( this );
}

