//
// main.cpp
//

#include "host.h"

int main(int argc, char *argv[])
{
    SDL_Window* window = SDL_CreateWindow("Race", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, INITIAL_WIDTH, INITIAL_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    if (window == NULL) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        exit(0);
    }
    Host host(window);
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    host.resize(w, h);
    host.initialize();
    host.render();
    SDL_Event ev;
    while (host.is_running()) {
        while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT) {
                host.quit_event();
            } else if (ev.type == SDL_WINDOWEVENT) {
                host.window_event(&ev);
            } else if (ev.type == SDL_KEYDOWN) {
                host.key_press_event(&ev);
            } else if (ev.type == SDL_KEYUP) {
                host.key_release_event(&ev);
            } else if (ev.type == SDL_MOUSEBUTTONDOWN) {
                host.mouse_press_event(&ev);
            } else if (ev.type == SDL_MOUSEBUTTONUP) {
                host.mouse_release_event(&ev);
            } else if (ev.type == SDL_MOUSEMOTION) {
                host.mouse_move_event(&ev);
            } else if (ev.type == SDL_MOUSEWHEEL) {
                host.mouse_wheel_event(&ev);
            }
        }
        host.render();
        SDL_Delay(1);
    }
    SDL_DestroyWindow(window);
    return 0;
}
