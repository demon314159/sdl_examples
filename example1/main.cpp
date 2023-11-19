#include "SDL.h"   /* All SDL App's need this */
#include <stdio.h>

int main(int argc, char *argv[]) {
    SDL_Window* window = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Video Initialization Error: %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow("My Stuff", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
