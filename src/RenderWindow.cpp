#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char *title)
    : window(NULL), renderer(NULL), width(1), height(1)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (!window)
        std::cout << "SDL_CreateWindow HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
        std::cout << "SDL_CreateRenderer HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
}

SDL_Texture *RenderWindow::loadTexture(const char *file_path)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, file_path);
    if (!texture)
        std::cout << "IMG_LoadTexture HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_SetWindowSize(window, width, height);
    return texture;
}

SDL_Texture *RenderWindow::loadTextureAccess(const char *file_path, int access)
{
    SDL_Surface *surface = NULL; 
    SDL_Texture *texture = NULL, *tmp = NULL;
    
    surface = IMG_Load(file_path);
    if(NULL == surface)
    {
        std::cout << "IMG_Load HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return NULL;
    }

    tmp = SDL_CreateTextureFromSurface(renderer, surface);
    if(NULL == tmp)
    {
        std::cout << "SDL_CreateTextureFromSurface HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return NULL;
    }
    SDL_QueryTexture(tmp, NULL, NULL, &width, &height);
    SDL_SetWindowSize(window, width, height);
    
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, access, surface->w, surface->h);
    if(NULL == texture) 
    {
        std::cout << "SDL_CreateTextureFromSurface HAS FAILED. SDL_ERROR: " <<  SDL_GetError() << std::endl;
        return NULL;
    }
    SDL_SetRenderTarget(renderer, texture); /* La cible de rendu est maintenant texture. */
    SDL_RenderCopy(renderer, tmp, NULL, NULL); /* On copie tmp sur texture */
    SDL_DestroyTexture(tmp);
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(renderer, NULL); /* La cible de rendu est de nouveau le renderer. */
    
    return texture;
}

SDL_Texture * RenderWindow::loadTextureFromSurface(SDL_Surface * surface, int access)
{
    SDL_Texture *texture = NULL, *tmp = NULL;
    
    tmp = SDL_CreateTextureFromSurface(renderer, surface);
    if(NULL == tmp)
    {
        std::cout << "SDL_CreateTextureFromSurface HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return NULL;
    }
    SDL_QueryTexture(tmp, NULL, NULL, &width, &height);
    SDL_SetWindowSize(window, width, height);
    
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, access, surface->w, surface->h);
    if(NULL == texture) 
    {
        std::cout << "SDL_CreateTextureFromSurface HAS FAILED. SDL_ERROR: " <<  SDL_GetError() << std::endl;
        return NULL;
    }
    SDL_SetRenderTarget(renderer, texture); /* La cible de rendu est maintenant texture. */
    SDL_RenderCopy(renderer, tmp, NULL, NULL); /* On copie tmp sur texture */
    SDL_DestroyTexture(tmp);
    SDL_SetRenderTarget(renderer, NULL); /* La cible de rendu est de nouveau le renderer. */
    
    return texture;
}


SDL_Surface * RenderWindow::loadSurface(const char *file_path)
{
    SDL_Surface *surface = NULL;
    surface = IMG_Load(file_path);
    if(NULL == surface)
    {
        std::cout << "IMG_Load HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return NULL;
    }
    return surface;

}

void RenderWindow::clear()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
}


void RenderWindow::render(SDL_Texture * texture)
{
    
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}


void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::CleanUp()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

SDL_Renderer * RenderWindow::getRenderer()
{
    return renderer;
}
    


