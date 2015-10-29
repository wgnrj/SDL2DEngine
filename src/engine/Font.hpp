#ifndef _FONT_HPP_
#define _FONT_HPP_

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class LFont
{
    private:
        TTF_Font* mFont;

        std::string mFontFile;
        int mPointSize;

    public:
        LFont( std::string fontFile, int pointSize );
        ~LFont();

        TTF_Font* getFont();
        int getPointSize();
};

#endif

