#ifndef _DISPLAY_HPP_
#define _DISPLAY_HPP_

#include "Window.hpp"

class Display
{
    private:
        int mDisplayID;

        int mWidth;
        int mHeight;

        Window* mWindow;

    public:
        int getWidth();
        int getHeight();
};

#endif

