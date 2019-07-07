/* 
 * hello1SDL.c - Initializes SDL
 */
#include <stdio.h>
#include <SDL2/SDL.h>

int main(void)
{
    // attempt to initialize graphics system
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error intializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    printf("SDL initialization successful!\n");

    // Clean Up resources before exiting
    SDL_Quit();
    return 0;
}