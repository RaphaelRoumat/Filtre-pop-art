#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include "RenderWindow.hpp"
#include "Logic.hpp"
#include "stdlib.h"

typedef std::string String;

int main(int argc, char *args[])
{
    srand(time(0));
    /* Iniatilisation de SDL */
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return 0;
    }

    /* Iniatilisation de l'addon SDL_image */
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return 0;
    }

    RenderWindow window("Générateur de pop art");

    String path;
    std::cout << "Image: ";
    std::cin >> path;

    int color_count;
    std::cout << "Number of colors: ";
    std::cin >> color_count;

    int image_count;
    std::cout << "Number of image to generate: ";
    std::cin >> image_count;

    
    SDL_Texture *texture;
    SDL_Surface *surface;

    for (int i = 0; i < image_count; i++)
    {
        surface = window.loadSurface(path.c_str());
        Logic logic(surface, color_count);
        logic.GeneratePopArt();
        std::ostringstream stringStream;
        stringStream << "save/result" << i << ".png";
        std::string copyOfStr = stringStream.str();
        IMG_SavePNG(surface, copyOfStr.c_str());
    }

    texture = window.loadTextureFromSurface(surface, SDL_TEXTUREACCESS_TARGET);

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            default:
                break;
            }
        }
        window.clear();
        window.render(texture);
        window.display();
    }

    window.CleanUp();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
