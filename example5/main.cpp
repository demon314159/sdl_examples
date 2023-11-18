
#include "view.h"

int main(int argc, char *argv[]) {
    View view;
    view.initialize();
    view.render();
    bool is_running = true;
    SDL_Event ev;
    while(is_running) {
//        while(SDL_PollEvent(&ev) != 0) {
        if (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT) {
                is_running = false;
            }
        }
        view.render();
//        SDL_Delay(50);
    }
    return 0;
}
