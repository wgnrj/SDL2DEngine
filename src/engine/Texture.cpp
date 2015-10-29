#include "Texture.hpp"

LTexture::LTexture()
    : mTexture( NULL ), mWidth( 0 ), mHeight( 0 ), mManipulable( false ), mPixels( NULL ), mPitch( 0 )
{
}

LTexture::~LTexture()
{
    free();
}

bool
LTexture::loadFromFile( SDL_Renderer* renderer, std::string path )
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if ( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface( loadedSurface );
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

bool
LTexture::loadFromRenderedText( SDL_Renderer* renderer, LFont* font, std::string textureText, SDL_Color textColor )
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid( font->getFont(), textureText.c_str(), textColor );
    if ( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if ( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface( textSurface );
    }

    return mTexture != NULL;
}

void
LTexture::free()
{
    if ( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );

        mTexture = NULL;

        mWidth = 0;
        mHeight = 0;
    }
}

void
LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void
LTexture::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( mTexture, blending );
}

void
LTexture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void
LTexture::render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if ( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int
LTexture::getWidth()
{
    return mWidth;
}

int
LTexture::getHeight()
{
    return mHeight;
}

bool
LTexture::isManipulable()
{
    return mManipulable;
}

bool
LTexture::loadManipulableFromFile( SDL_Renderer* renderer, std::string path )
{
    free();

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if ( loadedSurface == NULL )
    {
        printf( "Unable to load image %s!, SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL );

        mPixelFormat = new SDL_PixelFormat( *( formattedSurface->format ) );

        if ( formattedSurface == NULL )
        {
            printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            mTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );

            if ( mTexture == NULL )
            {
                printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                setBlendMode( SDL_BLENDMODE_BLEND );

                mManipulable = true;

                lockTexture( &formattedSurface->clip_rect );

                memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

                mWidth = formattedSurface->w;
                mHeight = formattedSurface->h;

                Uint32* pixels = (Uint32*) mPixels;

                int pixelCount = ( mPitch / 4 ) * mHeight;

                Uint32 colorKey = SDL_MapRGB( formattedSurface->format, 0x00, 0xFF, 0xFF );
                Uint32 transparentKey = SDL_MapRGBA( formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00 );

                for ( int i = 0; i < pixelCount; ++i )
                {
                    if ( pixels[ i ] == colorKey )
                    {
                        pixels[ i ] = transparentKey;
                    }
                }

                unlockTexture();
                mPixels = NULL;
            }

            SDL_FreeSurface( formattedSurface );
        }

        SDL_FreeSurface( loadedSurface );
    }

    return mTexture != NULL;
}

bool
LTexture::lockTexture( SDL_Rect* lockedRect )
{
    if ( !isManipulable() )
    {
        printf( "Texture is not manipulable!\n" );
        return false;
    }

    if ( mPixels != NULL )
    {
        printf( "Texture is already locked!\n" );
        return false;
    }

    if ( SDL_LockTexture( mTexture, lockedRect, &mPixels, &mPitch ) != 0 )
    {
        printf( "Unable to lock texture! %s\n", SDL_GetError() );
        return false;
    }

    return true;
}

bool
LTexture::unlockTexture()
{
    if ( !isManipulable() )
    {
        printf( "Texture is not manipulable!\n" );
        return false;
    }

    if ( mPixels == NULL )
    {
        printf( "Texture is not locked!\n" );
        return false;
    }

    SDL_UnlockTexture( mTexture );
    mPixels = NULL;
    mPitch = 0;

    return true;
}

void*
LTexture::getPixels()
{
    return mPixels;
}

int
LTexture::getPitch()
{
    return mPitch;
}

Uint32
LTexture::getPixel32( unsigned int x, unsigned int y )
{
    Uint32* pixels = (Uint32*) mPixels;

    return pixels[ ( y * ( mPitch / 4 ) ) + x ];
}

void
LTexture::alpha( SDL_Rect* rect )
{
    lockTexture( rect );

    Uint32* pixels = (Uint32*) mPixels;
    int pixelCount = ( mPitch / 4 ) * rect->h;

    Uint32 transparent = SDL_MapRGBA( mPixelFormat, 0xFF, 0xFF, 0xFF, 0x00 );

    // TODO: iterate over figure texture and "inverse" transparent on background
    for ( int i = 0; i < pixelCount; ++i )
    {
        pixels[i] = transparent;
    }

    unlockTexture();
}

