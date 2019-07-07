/* 
 * hello2SDL.c - Initializes SDL
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

    SDL_Window *gameWindow = SDL_CreateWindow("Isle of Doldrum", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    if(!gameWindow)
    {
        printf("Error in creating game window: %s\n", SDL_GetError());
    }

    // Wait
    SDL_Delay(5000);

    // Clean Up resources before exiting
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();
    return 0;
}