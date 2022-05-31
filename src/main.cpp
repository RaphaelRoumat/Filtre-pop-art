#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string.h>
#include "RenderWindow.hpp"
#include "Logic.hpp"

typedef std::string String;

int main(int argc, char *args[])
{ 
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

    std::cout << "Image: ";
    String path;
    std::cin >> path;

    SDL_Surface * surface = window.loadSurface(path.c_str());

    Logic logic(surface, 3);

    logic.GeneratePopArt();
    IMG_SavePNG(surface, "result.png");
    SDL_Texture * texture = window.loadTextureFromSurface(surface, SDL_TEXTUREACCESS_TARGET);
    

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT :
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
