#include "SDL.h"   /* All SDL App's need this */
#include <stdio.h>

int main(int argc, char *argv[]) {
    SDL_Window* window = nullptr;
    SDL_Surface* window_surface = nullptr;
    SDL_Surface* image_surface = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Video Initialization Error: %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow("My Stuff", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        return -1;
    }
    window_surface = SDL_GetWindowSurface(window);
    image_surface = SDL_LoadBMP("test.bmp");
    if (image_surface == NULL) {
        printf("BMP Load Error: %s\n", SDL_GetError());
    } else {
        SDL_BlitSurface(image_surface, NULL, window_surface, NULL);
        SDL_UpdateWindowSurface(window);
        bool is_running = true;
        SDL_Event ev;
        while(is_running) {
            while(SDL_PollEvent(&ev) != 0) {
                if (ev.type == SDL_QUIT) {
                    is_running = false;
                }
            }
            SDL_UpdateWindowSurface(window);
            SDL_Delay(50);
        }
    }
    SDL_FreeSurface(image_surface);
    image_surface = nullptr;
    SDL_FreeSurface(window_surface);
    window_surface = nullptr;

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
