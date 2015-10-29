#include "Window.hpp"

Window::Window()
    : mWidth( 0 ), mHeight( 0 ), mWindowID( 0 ), mWindow( NULL ), mRenderer( NULL ), mMinimized( false ), mFullScreen( false ), mMouseFocus( false ), mKeyboardFocus( false )
{
}

Window::~Window()
{
}

void
Window::focus()
{
    if ( !mShown )
    {
        SDL_ShowWindow( mWindow );
    }

    SDL_RaiseWindow( mWindow );
}

void
Window::render()
{
    if ( !mMinimized )
    {
        mRenderer->clear();
        mRenderer->render();
    }
}

void
Window::handleEvent( SDL_Event& e )
{
    if ( e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID )
    {
        switch ( e.window.event )
        {
            case SDL_WINDOWEVENT_SHOWN:
                mShown = true;
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                mShown = false;
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                mWidth = e.window.data1;
                mHeight = e.window.data2;
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                break;
            case SDL_WINDOWEVENT_ENTER:
                mMouseFocus = true;
                break;
            case SDL_WINDOWEVENT_LEAVE:
                mMouseFocus = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                mKeyboardFocus = true;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                mKeyboardFocus = false;
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                mMinimized = true;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                mMinimized = false;
                break;
            case SDL_WINDOWEVENT_RESTORED:
                mMinimized = false;
                break;
            case SDL_WINDOWEVENT_CLOSE:
                break;
        }
    }
}

