#include "Font.hpp"

LFont::LFont( std::string fontFile, int pointSize )
    : mFont( NULL ), mFontFile( fontFile ), mPointSize( pointSize )
{
    mFont = TTF_OpenFont( fontFile.c_str(), pointSize );
}

LFont::~LFont()
{
    TTF_CloseFont( mFont );
    mFont = NULL;
}

TTF_Font*
LFont::getFont()
{
    return mFont;
}

int
LFont::getPointSize()
{
    return mPointSize;
}

