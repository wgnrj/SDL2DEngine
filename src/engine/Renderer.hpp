#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <SDL2/SDL.h>

class Renderer
{
    private:
        SDL_Renderer* mRenderer;

    public:
        Renderer();
        ~Renderer();

        void clear();
        void render();
};

#endif

