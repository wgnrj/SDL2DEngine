#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <string>

#include <SDL2/SDL.h>

#include "Renderer.hpp"

class Window
{
    private:
        int mWidth;
        int mHeight;

        int mWindowID;

        std::string mWindowTitle;

        SDL_Window* mWindow;

        Renderer* mRenderer;

        bool mMinimized;
        bool mFullScreen;
        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mShown;


    public:
        Window();
        ~Window();

        Renderer* createRenderer();
        void handleEvent( SDL_Event& e );

        void setWindowTitle( std::string windowTitle );

        void focus();
        void render();

        int getWidth();
        int getHeight();

        bool isMinimized();
        bool hasMouseFocus();
        bool hasKeyboardFocus();
};

#endif

