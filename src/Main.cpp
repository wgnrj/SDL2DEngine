#include "Main.hpp"

Game::Game()
    : paused( false ), running( true ), quit( false ), r( 0xFF ), g( 0xFF ), b( 0xFF ), a( 0xFF ), x( 240 ), y( 190 ), screenWidth( SCREEN_WIDTH ), screenHeight( SCREEN_HEIGHT ), gWindow( NULL ), gRenderer( NULL ), gGameController( NULL ), gGameControllerHaptic( NULL ), e(), gBackgroundTexture(), gForegroundTexture(), gFigureTexture(), gCoinTexture(), gCoin(), moveUp( false ), moveDown( false ), moveLeft( false ), moveRight( false ), t( 0 ), gMusic( NULL ), gChunk( NULL ), fpsTimer(), countedFrames( 0 ), JOYSTICK_DEAD_ZONE( 8000 )
{
}

Game::~Game()
{
//    onClose();
}

bool
Game::onInit()
{
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    if ( ( gWindow = SDL_CreateWindow( WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN ) ) == NULL)
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
/*SDL_Surface* gSurface = SDL_GetWindowSurface( gWindow );
SDL_PixelFormat* gPixelFormat = gSurface->format;
Uint32 gWindowPixelFormat = SDL_GetWindowPixelFormat( gWindow );
SDL_FreeSurface( gSurface );*/
    if ( ( gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ) ) == NULL )
    {
        printf( "Unable to create renderer! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    SDL_SetRenderDrawColor( gRenderer, r, g, b, a );

    int imageFlags = IMG_INIT_PNG;
    if ( !( IMG_Init( imageFlags ) & imageFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }

    if ( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }

    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    if ( SDL_NumJoysticks() < 1 )
    {
        printf( "Warning: No joysticks connected!\n" );
    }
    else
    {
        if ( SDL_IsGameController( 0 ) )
        {// TODO loop and dynamic and plugin/plugout
            gGameController = SDL_GameControllerOpen( 0 );
            if ( gGameController == NULL )
            {
                printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                gGameControllerHaptic = SDL_HapticOpenFromJoystick( SDL_GameControllerGetJoystick( gGameController ) );
                if ( gGameControllerHaptic == NULL )
                {
                    printf( "Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError() );
                }
                else
                {
                    if ( SDL_HapticRumbleInit( gGameControllerHaptic ) < 0 )
                    {
                        printf( "Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError() );
                    }
                }
            }
        }
    }

    gBackgroundTexture.loadFromFile( gRenderer, "data/images/background.png" );
    gForegroundTexture.loadManipulableFromFile( gRenderer, "data/images/foreground.png" );
    gFigureTexture.loadManipulableFromFile( gRenderer, "data/images/figure.png" );

    gCoinTexture.loadFromFile( gRenderer, "data/images/coin.png" );
    gCoin.addSpriteSheetTexture( &gCoinTexture );

    gMusic = Mix_LoadMUS( "data/sounds/beat.wav" );
    gChunk = Mix_LoadWAV( "data/sounds/scratch.wav" );

    fpsTimer.start();

    return true;
}

bool
Game::onEvent( SDL_Event *e )
{
    switch ( e->type )
    {
        case SDL_QUIT:
            quit = true;
            break;

        case SDL_KEYDOWN:
            switch ( e->key.keysym.sym )
            {
                case SDLK_UP:
                    moveUp = true;
                    moveDown = false;
                    break;
                case SDLK_LEFT:
                    moveRight = false;
                    moveLeft = true;
                    break;
                case SDLK_DOWN:
                    moveUp = false;
                    moveDown = true;
                    break;
                case SDLK_RIGHT:
                    moveRight = true;
                    moveLeft = false;
                    break;
                case SDLK_q:
                    if ( e->key.keysym.mod & KMOD_CTRL )
                    {
                        quit = true;
                    }
                    break;
            }
            break;

        case SDL_KEYUP:
            switch ( e->key.keysym.sym )
            {
                case SDLK_UP:
                    moveUp = false;
                    break;
                case SDLK_LEFT:
                    moveLeft = false;
                    break;
                case SDLK_DOWN:
                    moveDown = false;
                    break;
                case SDLK_RIGHT:
                    moveRight = false;
                    break;
                case SDLK_q:
                    if ( e->key.keysym.mod & KMOD_CTRL )
                    {
                        quit = true;
                    }
                    break;
            }
            break;

        case SDL_CONTROLLERBUTTONDOWN:
            switch ( e->cbutton.button )
            {
                case SDL_CONTROLLER_BUTTON_A:
                    Mix_PlayChannel( -1, gChunk, 0 );
                    break;
                case SDL_CONTROLLER_BUTTON_B:
                    break;
                case SDL_CONTROLLER_BUTTON_X:
                    if ( Mix_PlayingMusic() == 0 )
                    {
                        Mix_PlayMusic( gMusic, -1 );
                    }
                    else
                    {
                        if ( Mix_PausedMusic() == 1 )
                        {
                            Mix_ResumeMusic();
                        }
                        else
                        {
                            Mix_PauseMusic();
                        }
                    }
                    break;
                case SDL_CONTROLLER_BUTTON_Y:
                    Mix_HaltMusic();
                    break;
                case SDL_CONTROLLER_BUTTON_BACK:
                    break;
                case SDL_CONTROLLER_BUTTON_START:
                    quit = true;
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
            if ( SDL_HapticRumblePlay( gGameControllerHaptic, 0.5, 200 ) != 0 )
            {
                printf( "Warning: Unable to play rumble! SDL Error: %s\n", SDL_GetError() );
            }
            break;

        case SDL_CONTROLLERAXISMOTION:
            switch ( e->caxis.which )
            {
                case 0:
                    // X axis motion
                    if ( e->caxis.axis == 0 )
                    {
                        if ( e->caxis.value < -JOYSTICK_DEAD_ZONE )
                        {
                            moveLeft = true;
                            moveRight = false;
                        }
                        else if ( e->caxis.value > JOYSTICK_DEAD_ZONE )
                        {
                            moveLeft = false;
                            moveRight = true;
                        }
                        else
                        {
                            moveLeft = false;
                            moveRight = false;
                        }
                    }
                    else if ( e->caxis.axis == 1 )
                    {
                        if ( e->caxis.value < -JOYSTICK_DEAD_ZONE )
                        {
                            moveUp = true;
                            moveDown = false;
                        }
                        else if ( e->caxis.value > JOYSTICK_DEAD_ZONE )
                        {
                            moveUp = false;
                            moveDown = true;
                        }
                        else
                        {
                            moveUp = false;
                            moveDown = false;
                        }
                    }
                    break;
            }
            break;
    }

    return true;
}

bool
Game::onLoop()
{
    // remove part of background
    SDL_Rect currentRect;
    currentRect.x = x;
    currentRect.y = y;
    currentRect.w = 64;
    currentRect.h = 128;
    gForegroundTexture.alpha( &currentRect );

    if ( moveUp )
    {
        y -= 5;
    }

    if ( moveDown )
    {
        y += 5;
    }

    if ( moveRight )
    {
        x += 5;
    }

    if ( moveLeft )
    {
        x -= 5;
    }

    ++t;
    gCoin.nextPosition( t );

    float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
    if ( avgFPS > 2000000 )
    {
        avgFPS = 0;
    }
//    printf( "Average FPS: %.2f\n", avgFPS );

    ++countedFrames;

    return true;
}

bool
Game::onRender()
{
    SDL_SetRenderDrawColor( gRenderer, r, g, b, a );
    SDL_RenderClear( gRenderer );

    gBackgroundTexture.render( gRenderer, 0, 0 );
    gForegroundTexture.render( gRenderer, 0, 0 );
    gFigureTexture.render( gRenderer, x, y );

    gCoin.render( gRenderer );

    SDL_RenderPresent( gRenderer );

    return true;
}

bool
Game::onClose()
{
    Mix_FreeChunk( gChunk );
    gChunk = NULL;
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    SDL_HapticClose( gGameControllerHaptic );
    gGameControllerHaptic = NULL;
    SDL_GameControllerClose( gGameController );
    gGameController = NULL;

    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return true;
}

int
main( int argc, char *argv[] )
{
    Game game;

    game.onInit();

    while ( !game.quit )
    {
        while( SDL_PollEvent( &game.e ) != 0 )
        {
            game.onEvent( &game.e );
//            game.gController.handleEvent( game.e );
        }
//        game.gController.getLeftAxisDirection();
//        game.gController.getRightAxisDirection();
        game.onLoop();
        game.onRender();
    }

    game.onClose();

    return 0;
}

