#include "Logic.hpp"

Logic::Logic(SDL_Surface *surface, int color_count)
    : color_count(color_count), original(surface)
{
    width = surface->w;
    height = surface->h;
    height = surface->h;
    height = surface->h;
    height = surface->h;
}



Uint32 Logic::getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0; /* shouldn't happen, but avoids warnings */
    }
}

void Logic::getpixelRGB(SDL_Surface *surface, int x, int y, SDL_Color *rgb)
{
    SDL_GetRGB(getpixel(surface, x, y), surface->format, &rgb->r, &rgb->g, &rgb->b); //On appelle la fonction
}

void Logic::setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void Logic::grayscale()
{
    SDL_LockSurface(original);
    pixelsColors.reserve(width * height);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            Uint32 pixel = getpixel(original, x, y);

            Uint8 r, g, b;
            SDL_GetRGB(pixel, original->format, &r, &g, &b);

            // std::cout << "x: " << x << ", y: " << y << " #COLOR = " <<(int) r << ", " <<(int) g << ", " <<(int) b << std::endl;

            Uint8 average_color = (r + g + b) / 3;
            pixelsColors.emplace_back(average_color);

            Uint32 final_color = SDL_MapRGB(original->format, average_color, average_color, average_color);

            setPixel(original, x, y, final_color);
        }
    }

    SDL_UnlockSurface(original);
}

void Logic::sortPixels()
{

    pixelsColorsSorted = pixelsColors;

    std::sort(pixelsColorsSorted.begin(), pixelsColorsSorted.end());
}

std::vector<Uint8> Logic::findQuartiles()
{
    std::vector<Uint8> quartiles;
    int items_nbr = width * height;
    int quartiles_number = color_count;

    double coef = items_nbr / (quartiles_number + 1);

    for (int i = 1; i < (quartiles_number + 1); i++)
    {
        quartiles.push_back(pixelsColorsSorted[static_cast<int>(coef * i) - 1]);
    }

    return quartiles;
}

std::vector<SDL_Color> Logic::generateColors()
{
    srand(time(0)); // Initialize random number generator.
    std::vector<SDL_Color> colors;
    SDL_Color color = {0, 0, 0};

    colors.push_back(color);
    int min = 0, max = 255;
    for (int i = 1; i < color_count; i++)
    {
        color.r = min + (rand() % static_cast<int>(max - min + 1));
        color.g = min + (rand() % static_cast<int>(max - min + 1));
        color.b = min + (rand() % static_cast<int>(max - min + 1));

        colors.push_back(color);
    }

    return colors;
}

int Logic::closestColor(Uint8 *target, std::vector<Uint8> &quartiles)
{
    Uint8 current_diff = abs((*target) - quartiles[0]);
    int closest_index = 0;

    for (int i = 1; i < (int)quartiles.size(); i++)
    {
        if (abs((*target) - quartiles[i]) < current_diff)
        {
            current_diff = abs((*target) - quartiles[i]);
            closest_index = i;
        }
    }

    return closest_index;
}

void Logic::assignatePopArtColors(std::vector<SDL_Color> &colors, std::vector<Uint8> &quartilesColors)
{

    SDL_LockSurface(original);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            SDL_Color rgb;
            getpixelRGB(original, x, y, &rgb);

            // Uint8 current_color = pixelsColors[x + y * width];

            Uint8 current_color = rgb.g;
            int index = closestColor(&current_color, quartilesColors);

            rgb.r = colors[index].r;
            rgb.g = colors[index].g;
            rgb.b = colors[index].b;

            Uint32 final_color = SDL_MapRGB(original->format, rgb.r, rgb.g, rgb.b);

            setPixel(original, x, y, final_color);
        }
    }

    SDL_UnlockSurface(original);
}

void Logic::GeneratePopArt()
{
    grayscale();
    sortPixels();

    std::vector<Uint8> quartilesColors = findQuartiles();

    std::vector<SDL_Color> popArtColors = generateColors();

    assignatePopArtColors(popArtColors, quartilesColors);

    std::cout << "DONE" << '\n';
}
