#include <SDL.h>

#define SDL_MAIN_HANDLED
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failure %s\n", SDL_GetError());
        return 1;
    }
    SDL_Log("Success\n");
    SDL_Quit();
    return 0;
}