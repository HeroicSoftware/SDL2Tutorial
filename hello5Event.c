/**
* hello6Event.c - Move the sprite using the arrow keys 
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

// Speed in pixels/second
#define SPEED (300)

int main(void)
{
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *gameWindow = SDL_CreateWindow("Static Animation With Window Bounce", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!gameWindow)
    {
        printf("Error creating Window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer, which sets up the graphics hardware
    Uint32 renderFlags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *gameRenderer = SDL_CreateRenderer(gameWindow, -1, renderFlags);

    if (!gameRenderer)
    {
        printf("Error Creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        return 1;
    }

    // Load the image into memory using SDL_image library function
    SDL_Surface *spriteSurface = IMG_Load("resources/tinyGame.png");
    if (!spriteSurface)
    {
        printf("Error creating surface");
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        return 1;
    }

    // Load the image data into graphic hardware's memory
    SDL_Texture *spriteTexture = SDL_CreateTextureFromSurface(gameRenderer, spriteSurface);

    // Free the surface as it is no longer needed
    SDL_FreeSurface(spriteSurface);

    if (!spriteTexture)
    {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        return 1;
    }

    // Struct to hold the position and size of the sprite
    SDL_Rect spriteRectangle;

    // Get the dimensions of texture and scale them
    SDL_QueryTexture(spriteTexture, NULL, NULL, &spriteRectangle.w, &spriteRectangle.h);
    // spriteRectangle.w /= 4;
    // spriteRectangle.h /= 4;

    // Start the sprite in the center of the screen
    float xPosition = (WINDOW_WIDTH - spriteRectangle.w) / 2;
    float yPosition = (WINDOW_HEIGHT - spriteRectangle.h) / 2;

    // Give sprite inital Velocity
    float xSpeed = SPEED;
    float ySpeed = SPEED;



    // Set to 1 when Window Close button is pressed
    int closeWindow = 0;

    while (closeWindow == 0)
    {
        // Process Events
        SDL_Event gameEvent;
        while (SDL_PollEvent(&gameEvent))
        {
            // If the user clicks the 'X' button on window
            if (gameEvent.type == SDL_QUIT)
            {
                closeWindow = 1;
            }
        }

        if (xPosition <= 0)
        {
            xPosition = 0;
            xSpeed = -xSpeed;
        }
        if (yPosition <= 0)
        {
            yPosition = 0;
            ySpeed = -ySpeed;
        }
        if (xPosition >= (WINDOW_WIDTH - spriteRectangle.w))
        {
            xPosition = WINDOW_WIDTH - spriteRectangle.w;
            xSpeed = -xSpeed;
        }
        if (yPosition >= (WINDOW_HEIGHT - spriteRectangle.h))
        {
            yPosition = WINDOW_HEIGHT - spriteRectangle.h;
            ySpeed = -ySpeed;
        }

        // Update the sprite position
        yPosition += ySpeed / 60;
        xPosition += xSpeed / 60;

        // Set the positions in the spriteRect
        spriteRectangle.x = (int)xPosition;
        spriteRectangle.y = (int)yPosition;

        // Clear the window
        SDL_RenderClear(gameRenderer);

        // Draw the image to the window
        SDL_RenderCopy(gameRenderer, spriteTexture, NULL, &spriteRectangle);
        SDL_RenderPresent(gameRenderer);

        // Wait
        SDL_Delay(1000 / 60);
    }

    // Clean up before exiting
    SDL_DestroyTexture(spriteTexture);
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();

    return 0;
}