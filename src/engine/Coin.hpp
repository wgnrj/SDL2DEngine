#ifndef _COIN_HPP_
#define _COIN_HPP_

#include <SDL2/SDL.h>

#include "Texture.hpp"

#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1
#define COIN_FRAMES 7

class Coin
{
    private:
        const int centerX;
        const int centerY;

        int positionX;
        int positionY;

        const int radius;

        const int rotation;

        int frame;

        double omega;
        double phi;

        SDL_Rect spriteClips[ COIN_FRAMES ];
        LTexture* spriteSheetTexture;

    public:
        Coin();
        ~Coin();

        void addSpriteSheetTexture( LTexture* spriteSheetTexture );

        void nextPosition( int t );

        void render( SDL_Renderer* renderer );

        int getPosX();
        int getPosY();

        int getCurrentFrame();
};

#endif

