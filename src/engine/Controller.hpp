#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include <SDL2/SDL.h>

struct ControllerLayout
{
    int a;
    int b;
    int x;
    int y;

    int lb;
    int rb;
};

class Controller
{
    private:
        SDL_GameController* mGameController;
        SDL_Haptic* mHaptic;

        ControllerLayout mLayout;

        int mIndex;

        Sint16 mLeftXAxis;
        Sint16 mLeftYAxis;
        Sint16 mRightXAxis;
        Sint16 mRightYAxis;
        Sint16 mLeftTrigger;
        Sint16 mRightTrigger;

    public:
        const int JOYSTICK_DEAD_ZONE;

        Controller();
        Controller( int index );
        ~Controller();

        void handleEvent( SDL_Event& e );

        double getLeftAxisDirection();
        double getRightAxisDirection();
};

#endif

