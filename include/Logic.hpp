#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2_GFX.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <ctime>
typedef std::string String;

class Logic
{
    private:
        int width, height, color_count;
        SDL_Surface * original;
        std::vector<Uint8> pixelsColors;
        std::vector<Uint8> pixelsColorsSorted;
        Uint32 getpixel(SDL_Surface *surface, int x, int y);
        void getpixelRGB(SDL_Surface *surface, int x, int y, SDL_Color * rgb);
        void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
        void grayscale();
        void sortPixels();
        std::vector<Uint8> findQuartiles();
        std::vector<SDL_Color> generateColors();
        int closestColor(Uint8 * target, std::vector<Uint8> &quartiles);
        void assignatePopArtColors(std::vector<SDL_Color> &colors, std::vector<Uint8> &quartilesColors);

    public:
        Logic(SDL_Surface * surface, int color_count);
        void GeneratePopArt();
    
};