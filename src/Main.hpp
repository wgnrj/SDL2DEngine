#include <cstdio>
#include <cstdlib>

#include <cmath>

#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <glm/glm.hpp>

#include "engine/Logger.hpp"
#include "engine/Timer.hpp"

#include "engine/Condition.hpp"
#include "engine/Mutex.hpp"
#include "engine/Semaphore.hpp"

#include "engine/Display.hpp"
#include "engine/Renderer.hpp"
#include "engine/Window.hpp"

#include "engine/Controller.hpp"

#include "engine/Font.hpp"

#include "engine/Texture.hpp"

#include "engine/Coin.hpp"
#include "engine/Enemy.hpp"
#include "engine/EnemyController.hpp"
#include "engine/Figure.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define WINDOW_NAME "Game"

class Game
{
//    private:
    public:
        bool paused;
        bool running;
        bool quit;

        int r;
        int g;
        int b;
        int a;

        int t;

        int x;
        int y;

        bool moveUp;
        bool moveDown;
        bool moveLeft;
        bool moveRight;

        int screenWidth;
        int screenHeight;

        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
        SDL_Event e;

        SDL_GameController* gGameController;
        SDL_Haptic* gGameControllerHaptic;

//        Controller gController;

        const int JOYSTICK_DEAD_ZONE;

        LTexture gBackgroundTexture;
        LTexture gForegroundTexture;
        LTexture gFigureTexture;

        LTexture gCoinTexture;
        Coin gCoin;

        Mix_Music* gMusic;
        Mix_Chunk* gChunk;

        LTimer fpsTimer;
        int countedFrames;

    public:
        Game();
        ~Game();

        bool onInit();
        bool onEvent( SDL_Event* e );
        bool onLoop();
        bool onRender();
        bool onClose();
};

