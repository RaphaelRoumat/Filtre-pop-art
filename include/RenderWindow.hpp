#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <SDL2_GFX.h>

#include "RenderWindow.hpp"
#include "Logic.hpp"

class RenderWindow
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width, height;


public:
    RenderWindow(const char *title);
    SDL_Texture *loadTexture(const char *file_path);
    SDL_Texture *loadTextureAccess(const char *file_path, int access);
    SDL_Texture *loadTextureFromSurface(SDL_Surface * surface, int access);
    SDL_Surface *loadSurface(const char *file_path);
    void clear();
    void render(SDL_Texture * texture);
    void display();
    void CleanUp();
    SDL_Renderer * getRenderer();
};


