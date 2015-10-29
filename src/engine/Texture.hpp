#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Font.hpp"

class LTexture
{
    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;

        bool mManipulable;
        void* mPixels;
        int mPitch;
        SDL_PixelFormat* mPixelFormat;

    public:
        LTexture();
        ~LTexture();

        bool loadFromFile( SDL_Renderer* renderer, std::string path );
        bool loadManipulableFromFile( SDL_Renderer* renderer, std::string path );

        bool loadFromRenderedText( SDL_Renderer* renderer, LFont* font, std::string textureText, SDL_Color textColor );

        void free();

        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        void setBlendMode( SDL_BlendMode blending );

        void setAlpha( Uint8 alpha );

        void render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        int getWidth();
        int getHeight();

        bool isManipulable();
        bool lockTexture( SDL_Rect* lockedRect = NULL );
        bool unlockTexture();
        void* getPixels();
        int getPitch();
        Uint32 getPixel32( unsigned int x, unsigned int y );

        void alpha( SDL_Rect* rect );
};

#endif

