#include "Renderer.hpp"

Renderer::Renderer()
    : mRenderer( NULL )
{
}

Renderer::~Renderer()
{
}

void
Renderer::clear()
{
    SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( mRenderer );
}

void
Renderer::render()
{
    SDL_RenderPresent( mRenderer );
}

