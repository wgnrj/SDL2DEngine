#include "Condition.hpp"

Condition::Condition()
    : mCondition( SDL_CreateCond() )
{
}

Condition::Condition( Mutex* mutex )
    : mCondition( SDL_CreateCond() ), mMutex( mutex )
{
}

Condition::~Condition()
{
    SDL_DestroyCond( mCondition );
}

void
Condition::wait()
{
    // TODO check for attached mutex
    SDL_CondWait( mCondition, mMutex->getMutex() );
}

void
Condition::signal()
{
    SDL_CondSignal( mCondition );
}

void
Condition::attachMutex( Mutex* mutex )
{
    mMutex = mutex;
}

