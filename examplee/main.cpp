//
// main.cpp
//

#include "host.h"

int main(int argc, char *argv[])
{
    SDL_Window* window = SDL_CreateWindow("Plsy", INITIAL_WIDTH, INITIAL_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
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
            if (ev.type == SDL_EVENT_QUIT) {
                host.quit_event();
            } else if (ev.type == SDL_EVENT_WINDOW_RESIZED) {
                host.window_resized_event(&ev);
            } else if (ev.type == SDL_EVENT_KEY_DOWN) {
                host.key_press_event(&ev);
            } else if (ev.type == SDL_EVENT_KEY_UP) {
                host.key_release_event(&ev);
            } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                host.mouse_press_event(&ev);
            } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                host.mouse_release_event(&ev);
            } else if (ev.type == SDL_EVENT_MOUSE_MOTION) {
                host.mouse_move_event(&ev);
            } else if (ev.type == SDL_EVENT_MOUSE_WHEEL) {
                host.mouse_wheel_event(&ev);
            }
        }
        host.render();
        SDL_Delay(1);
    }
    SDL_DestroyWindow(window);
    return 0;
}
