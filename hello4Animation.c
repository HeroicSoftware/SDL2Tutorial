/**
 * hello4_animation.c - Animations scalegame.png scrolling up the window
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

// Speed in pixels/seconds
#define SCROLL_SPEED (300)

int main(void)
{
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Error initialzing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *gameWindow = SDL_CreateWindow("Gamepad and Star", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!gameWindow)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer, which sets up the graphics hardware
    Uint32 renderFlags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *render = SDL_CreateRenderer(gameWindow, -1, renderFlags);

    if (!render)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        return 1;
    }

    // Load the image into memory using SDL_image library function
    SDL_Surface *gameSurface = IMG_Load("resources/tinyGame.png");

    if (!gameSurface)
    {
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        return 1;
    }

    // Load the image data into the graphics hardware's memory
    SDL_Texture *gameTexture = SDL_CreateTextureFromSurface(render, gameSurface);
    SDL_FreeSurface(gameSurface);
    if (!gameTexture)
    {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        return 1;
    }

    // struct to hold the position and size of the sprite
    SDL_Rect spriteDest;

    // get the dimensions of texture
    SDL_QueryTexture(gameTexture, NULL, NULL, &spriteDest.w, &spriteDest.h);

    // Position the sprite at the bottom center of the window, origin is the top left corner, positive y is down
    spriteDest.x = (WINDOW_WIDTH - spriteDest.w) / 2;

    // require float resolution for y position
    float yPosition = WINDOW_HEIGHT;

    // Animation loop
    while (spriteDest.y >= -spriteDest.h)
    {
        // Clear the window
        SDL_RenderClear(render);

        // set the y postion in the struct
        spriteDest.y = (int)yPosition;

        // draw the image to the window
        SDL_RenderCopy(render, gameTexture, NULL, &spriteDest);
        SDL_RenderPresent(render);

        // Update sprite position
        yPosition -= (float)SCROLL_SPEED / 60;

        // Wait 1/60th of a second
        SDL_Delay(1000 / 60);
    }

    // Clean Up resources before exiting
    SDL_DestroyTexture(gameTexture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();

    return 0;
}