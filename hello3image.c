/**
 * hello3image.c - Initializes SDL, loads an image and displays it in a window
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

int main(void)
{
    // Attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initialzing SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *gameWindow = SDL_CreateWindow("GamePad and Star", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    if (!gameWindow)
    {
        printf("Error creating Window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer, which sets up the graphics hardware
    Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *render = SDL_CreateRenderer(gameWindow, -1, renderFlags);

    if (!render)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        return 1;
    }

    // Load the image into memory using SDL_Image Library function
    SDL_Surface *gameSurface = IMG_Load("resources/scalegame.png");

    if (!gameSurface)
    {
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        return 1;
    }

    // Load the image dat into the graphics hardware's memory
    SDL_Texture *gameTexture = SDL_CreateTextureFromSurface(render, gameSurface);

    // No longer need surface, free that memory. 
    SDL_FreeSurface(gameSurface);
    if(!gameTexture)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        return 1;
    }

    // Clear the window
    SDL_RenderClear(render);

    // Draw the image to the window
    SDL_RenderCopy(render, gameTexture, NULL, NULL);
    SDL_RenderPresent(render);

    // Wait a few seconds
    SDL_Delay(5000);

    // Clean up resources
    SDL_DestroyTexture(gameTexture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();

    return 0;
}