#include "Controller.hpp"

Controller::Controller( int index )
    : mIndex( index ), mLeftXAxis( 0 ), mLeftYAxis( 0 ), mRightXAxis( 0 ), mRightYAxis( 0 ), JOYSTICK_DEAD_ZONE( 8000 )
{
    if ( index < SDL_NumJoysticks() )
    {
        if ( SDL_IsGameController( 0 ) )
        {
            mGameController = SDL_GameControllerOpen( index );
            if ( mGameController == NULL )
            {
                printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                mHaptic = SDL_HapticOpenFromJoystick( SDL_GameControllerGetJoystick( mGameController ) );
                if ( mHaptic == NULL )
                {
                    printf( "Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError() );
                }
                else
                {
                    if ( SDL_HapticRumbleInit( mHaptic ) < 0 )
                    {
                        printf( "Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError() );
                    }
                }
            }
        }
    }
}

Controller::~Controller()
{
    SDL_HapticClose( mHaptic );
    mHaptic = NULL;
    SDL_GameControllerClose( mGameController );
    mGameController = NULL;
}

void
Controller::handleEvent( SDL_Event& e )
{
    if ( e.type == SDL_CONTROLLERBUTTONDOWN )
    {
        if ( e.cbutton.which != mIndex )
        {
            return;
        }

        switch ( e.cbutton.button )
        {
            case SDL_CONTROLLER_BUTTON_A:
                break;
            case SDL_CONTROLLER_BUTTON_B:
                break;
            case SDL_CONTROLLER_BUTTON_X:
                break;
            case SDL_CONTROLLER_BUTTON_Y:
                break;
            case SDL_CONTROLLER_BUTTON_BACK:
                break;
            case SDL_CONTROLLER_BUTTON_START:
                break;
            case SDL_CONTROLLER_BUTTON_LEFTSTICK:
                break;
            case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
                break;
            case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                break;
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                break;
        }
        if ( SDL_HapticRumblePlay( mHaptic, 0.5, 200 ) != 0 )
        {
            printf( "Warning: Unable to play rumble! SDL Error: %s\n", SDL_GetError() );
        }
    }

    if ( e.type == SDL_CONTROLLERAXISMOTION )
    {
        if ( e.caxis.which != mIndex )
        {
            return;
        }

        switch ( e.caxis.axis )
        {
            case SDL_CONTROLLER_AXIS_LEFTX:
                mLeftXAxis = e.caxis.value;
                break;
            case SDL_CONTROLLER_AXIS_LEFTY:
                mLeftYAxis = e.caxis.value;
                break;
            case SDL_CONTROLLER_AXIS_RIGHTX:
                mRightXAxis = e.caxis.value;
                break;
            case SDL_CONTROLLER_AXIS_RIGHTY:
                mRightYAxis = e.caxis.value;
                break;
            case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                mLeftTrigger = e.caxis.value;
                break;
            case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                mRightTrigger = e.caxis.value;
                break;
        }
    }
}

double
Controller::getLeftAxisDirection()
{
    if ( mLeftXAxis == 0 )
    {
        return .0L;
    }

    printf( "X: %d, Y: %d, R: %f\n", mLeftXAxis, mLeftYAxis, atan2( mLeftYAxis, mLeftXAxis ) );

    if ( mLeftYAxis < 0 )
    {
        return ( 2 * M_PI - atan2( mLeftYAxis, mLeftXAxis ) );
    }
    return atan2( mLeftYAxis, mLeftXAxis );
}

double
Controller::getRightAxisDirection()
{
    if ( mRightXAxis == 0 )
    {
        return .0L;
    }

    printf( "X: %d, Y: %d, R: %f\n", mRightXAxis, mRightYAxis, atan2( mRightYAxis, mRightXAxis ) );
    return atan2( mRightYAxis, mRightXAxis );
}

