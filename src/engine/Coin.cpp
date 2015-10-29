#include "Coin.hpp"

Coin::Coin()
    : centerX( 300 ), centerY( 150 ), positionX( 0 ), positionY( 0 ), radius( 20 ), rotation( CLOCKWISE ), frame( 0 ), omega( 0.1 ), phi( 0.0 ), spriteSheetTexture( NULL )
{
    for ( int i = 0; i < COIN_FRAMES; ++i )
    {
        spriteClips[ i ].x = i * 50;
        spriteClips[ i ].y = 0;
        spriteClips[ i ].w = 50;
        spriteClips[ i ].h = 50;
    }

    nextPosition( 0 );
}

Coin::~Coin()
{
}

void
Coin::addSpriteSheetTexture( LTexture* spriteSheetTexture )
{
    this->spriteSheetTexture = spriteSheetTexture;
}

void
Coin::nextPosition( int t )
{
    phi = omega * t;

    positionX = centerX + radius * cos( phi );
    if ( rotation == CLOCKWISE )
    {
        positionY = centerY + radius * sin( phi );
    }
    else
    {
        positionY = centerY - radius * sin( phi );
    }
}

void
Coin::render( SDL_Renderer* renderer )
{
    int currentFrame = getCurrentFrame() / 4;

    spriteSheetTexture->render( renderer, getPosX(), getPosY(), &spriteClips[ currentFrame ] );
}

int
Coin::getPosX()
{
    return positionX;
}

int
Coin::getPosY()
{
    return positionY;
}

// TODO bad
int
Coin::getCurrentFrame()
{
    frame += 1;
    if ( frame / 4 >= COIN_FRAMES )
    {
        frame = 0;
    }

    return frame;
}

